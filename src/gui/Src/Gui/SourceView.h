#pragma once

#include <QWidget>
#include <AbstractStdTable.h>

class FileLines;
class CommonActions;

class SourceView : public AbstractStdTable
{
    Q_OBJECT
public:
    SourceView(QString path, duint addr, QWidget* parent = nullptr);
    ~SourceView();

    QString getCellContent(duint row, duint column) override;
    duint getCellUserdata(duint row, duint column) override;
    bool isValidIndex(duint row, duint column) override;
    void sortRows(duint column, bool ascending) override;
    void prepareData() override;

    QString getSourcePath();
    void setSelection(duint addr);
    void clear();

private slots:
    void contextMenuSlot(const QPoint & pos);
    void gotoLineSlot();
    void openSourceFileSlot();
    void showInDirectorySlot();

private:
    MenuBuilder* mMenuBuilder = nullptr;
    CommonActions* mCommonActions = nullptr;
    QString mSourcePath;
    duint mModBase;
    int mTabSize = 4; //TODO: make customizable?

    FileLines* mFileLines = nullptr;

    enum
    {
        ColAddr,
        ColLine,
        ColCode,
    };

    struct CodeData
    {
        QString code;
    };

    struct LineData
    {
        duint addr;
        size_t index;
        CodeData code;
    };

    dsint mPrepareTableOffset = 0;
    std::vector<LineData> mLines;

    void setupContextMenu();
    void loadFile();
    void parseLine(size_t index, LineData & line);
    duint addrFromIndex(size_t index);
};
