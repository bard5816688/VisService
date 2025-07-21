#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include "BaseNode.h"
#include "BasicDefs.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

VISSERVICE_NAMESPACE_BEGIN

class InputBindingResolver 
{
public:
	static void resolve(const QJsonObject& flowJson, std::map<std::string, std::shared_ptr<BaseNode>>& nodes, const std::unordered_map<std::string, std::string>& globalVars)
	{
		QJsonArray nodesArray = flowJson["nodes"].toArray();
		for (const QJsonValue& nodeValue : nodesArray)
		{
			QJsonObject nodeDef = nodeValue.toObject();
			std::string nodeId = nodeDef["id"].toString().toStdString();
			auto nodeIt = nodes.find(nodeId);
			if (nodeIt == nodes.end()) continue;

			auto& node = nodeIt->second;

			if (!nodeDef.contains("input_bindings")) continue;

			QJsonObject inputBindings = nodeDef["input_bindings"].toObject();
			for (auto it = inputBindings.begin(); it != inputBindings.end(); ++it)
			{
				std::string inputKey = it.key().toStdString();
				std::string sourceStr = it.value().toString().toStdString();

				if (sourceStr.rfind("$global.", 0) == 0)
				{
					std::string varName = sourceStr.substr(8);
					auto it = globalVars.find(varName);
					if (it != globalVars.end())
					{
						node->inputs_[inputKey] = it->second;
					}
					else
					{
						std::cerr << "Global var " << varName << " not found\n";
					}
				}
				else
				{
					auto pos = sourceStr.find('.');
					if (pos == std::string::npos)
					{
						std::cerr << "Invalid binding string: " << sourceStr << "\n";
						continue;
					}
					std::string srcNodeId = sourceStr.substr(0, pos);
					std::string srcOutputKey = sourceStr.substr(pos + 1);

					auto srcNodeIt = nodes.find(srcNodeId);
					if (srcNodeIt == nodes.end())
					{
						std::cerr << "Source node " << srcNodeId << " not found\n";
						continue;
					}

					auto& srcNode = srcNodeIt->second;
					node->bindInput(inputKey, &srcNode->outputs_[srcOutputKey]);
				}
			}
		}
	}
};

VISSERVICE_NAMESPACE_END
