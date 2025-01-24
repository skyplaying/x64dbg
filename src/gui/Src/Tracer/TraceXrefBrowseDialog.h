#pragma once

#include "Bridge.h"
#include "ActionHelpers.h"
#include <QDialog>
#include <QListWidgetItem>
#include "TraceFileReader.h"

namespace Ui
{
    class TraceXrefBrowseDialog;
}

class TraceXrefBrowseDialog : public QDialog, public ActionHelper<TraceXrefBrowseDialog>
{
    Q_OBJECT

public:
    explicit TraceXrefBrowseDialog(QWidget* parent);
    ~TraceXrefBrowseDialog();
    using GotoFunction = std::function<void(duint)>;
    void setup(duint index, duint address, TraceFileReader* traceFile, GotoFunction gotoFunction);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_listWidget_itemSelectionChanged();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_XrefBrowseDialog_rejected();
    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_listWidget_customContextMenuRequested(const QPoint & pos);

    void copyThisSlot();
    void copyAllSlot();

private:
    Ui::TraceXrefBrowseDialog* ui;

    void changeAddress(duint address);
    void setupContextMenu();
    static QString GetFunctionSymbol(duint addr);

    typedef struct
    {
        TRACEINDEX index;
        duint addr;
    } TRACE_XREF_RECORD;
    std::vector<TRACE_XREF_RECORD> mXrefInfo;
    duint mAddress;
    int mPrevSelectionSize;
    MenuBuilder* mMenu;
    GotoFunction mGotoFunction;
};
