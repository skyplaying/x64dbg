#pragma once

#include <QWidget>
#include <QTabWidget>
#include "NotepadView.h"
#include "Bridge.h"

class NotesManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit NotesManager(QWidget* parent = nullptr);

public slots:
    void dbgStateChangedSlot(DBGSTATE state);

private:
    NotepadView* mGlobal;
    NotepadView* mDebuggee;
};
