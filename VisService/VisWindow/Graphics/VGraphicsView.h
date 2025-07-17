#pragma once
#include <QGraphicsView>
#include "qevent.h"

class QXmlStreamReader;
namespace VisWindow
{
    class VGraphicsItemGroup;
	class VGraphicsView : public QGraphicsView
	{
        Q_OBJECT

    public:
        VGraphicsView(QGraphicsScene* scene);
        void ZoomIn();
        void ZoomOut();
        void NewFile();
        bool LoadFile(const QString& fileName);
        bool Save();
        bool SaveAs();
        bool SaveFile(const QString& fileName);
        QString UserFriendlyCurrentFile();
        QString CurrentFile();
        void SetModified(bool value);
        bool IsModified() const;

    protected:
        virtual void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
        virtual void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        virtual void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
        virtual void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;

    private:
        bool MaybeSave();
        void SetCurrentFile(const QString& fileName);
        QString StrippedName(const QString& fullFileName);
        void LoadCanvas(QXmlStreamReader* xml);
        VGraphicsItemGroup* loadGroupFromXML(QXmlStreamReader* xml);
        QString curFile;
        bool m_untitled;
        bool m_modified;

    signals:
        void Signals_positionChanged(int x, int y);

	};

}

