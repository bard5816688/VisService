#pragma once
#include <QString>
#include <QVector>

namespace MN_VisionAlgorithm
{
	const long long AUTHORITY_GENERALUI = 4001000000;				//视觉通用算法配置 
	const long long AUTHORITY_GENERALUI_TASK = 4001010000;		    //视觉通用算法任务选择配置 

	const long long AUTHORITY_CALIBTRATEUI = 4002000000;			//标定界面

	const long long AUTHORITY_IMGSETTINGBAR = 4003000000;			//图像菜单栏  配置了这个下面的按钮才起效
	const long long AUTHORITY_DEBUGCONFIG = 4003010000;			    //调试配置
	const long long AUTHORITY_VISIONCONFIG = 4003020000;			//视觉任务配置
	const long long AUTHORITY_SAVEIMG = 4003030000;					//保存图像
	const long long AUTHORITY_MOVE = 4003040000;					//移动功能
	const long long AUTHORITY_LIGHTCAMERASETTING = 4003050000;		//光源相机参数设置
	//visible
 
	struct MS_AuthorityInfo
	{
		QString m_userID;             //用户账号（工号）
		QString m_userName;           //用户姓名
		QString m_roleName;           //权限角色名
		QVector<long long> m_permItems;     //详细权限功能项
		int m_id;                     //user数据的自增id，需要的自取
		MS_AuthorityInfo() :m_userID(""), m_userName(""), m_roleName(""), m_id(0)
		{
		}

	};
	//数据库信息相关
	struct MS_AuthorityDatabaseColumnInfo
	{
		MS_AuthorityDatabaseColumnInfo(const QString& _name, const QString& _type, const QString& _null, const QString& _unique) :m_columnName(_name), m_columnNull(_null), m_columnType(_type), m_columnUnique(_unique)
		{
		}
		QString m_columnName;
		QString m_columnType;
		QString m_columnNull;
		QString m_columnUnique;
	};

}
