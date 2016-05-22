#ifndef WORLDEDITORTOOLBOX_H
#define WORLDEDITORTOOLBOX_H

#include <QWidget>

#include "WorldEditor.h"

namespace Ui {
class WorldEditorToolBox;
}

class WorldEditorToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit WorldEditorToolBox(QWidget *parent = 0);
    ~WorldEditorToolBox();

signals:
    void worldSizeChanged();
    void brushSizeChanged(int size);
    void brushTypeChanged(WorldEditor::Tools tool);

private slots:
    void emitWorldSize();
    void emitBrushSize();
    void emitBrushType();

private:
    Ui::WorldEditorToolBox *ui;
};

#endif // WORLDEDITORTOOLBOX_H
