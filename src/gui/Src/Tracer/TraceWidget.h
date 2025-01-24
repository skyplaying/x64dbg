#pragma once

#include <QWidget>
#include "Bridge.h"
#include "TraceFileReader.h"

class QVBoxLayout;
class QPushButton;
class CPUWidget;
class TraceRegisters;
class TraceBrowser;
class TraceFileDumpMemoryPage;
class TraceInfoBox;
class TraceDump;
class TraceStack;
class TraceXrefBrowseDialog;

namespace Ui
{
    class TraceWidget;
}

class TraceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TraceWidget(Architecture* architecture, const QString & fileName, QWidget* parent);
    ~TraceWidget();

    inline TraceFileReader* getTraceFile() const
    {
        return mTraceFile;
    };
    inline TraceBrowser* getTraceBrowser() const
    {
        return mTraceBrowser;
    };
    inline TraceDump* getTraceDump() const
    {
        return mDump;
    };
    inline TraceStack* getTraceStack() const
    {
        return mStack;
    };
    // Enable trace dump and load it fully before searching. Return false if the user cancels.
    bool loadDumpFully();
    void setupFollowMenu(QMenu* menu);
public slots:
    // Enable trace dump in order to use these features. Return false if the user cancels.
    bool loadDump();

signals:
    void closeFile();
    void displayLogWidget();

protected slots:
    void displayLogWidgetSlot();
    void traceSelectionChanged(TRACEINDEX selection);
    void parseFinishedSlot();
    void closeFileSlot();
    void xrefSlot(duint addr);
    void followActionSlot();

protected:
    TraceFileReader* mTraceFile;
    TraceBrowser* mTraceBrowser;
    TraceInfoBox* mInfo;
    TraceDump* mDump;
    TraceRegisters* mGeneralRegs;
    TraceFileDumpMemoryPage* mMemoryPage;
    TraceStack* mStack;
    TraceXrefBrowseDialog* mXrefDlg;

    QPushButton* mLoadDump;
    Architecture* mArchitecture;

private:
    Ui::TraceWidget* ui;
    void setupDumpInitialAddresses(TRACEINDEX selection);
    void addFollowMenuItem(QMenu* menu, QString name, duint value);
};
