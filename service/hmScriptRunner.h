#ifndef HMSCRIPTRUNNER_H
#define HMSCRIPTRUNNER_H

#include "hmListService.h"

#include <QStringList>

namespace SDPO {

// TestList operations
static QString TL_NEW    = QStringLiteral("NewTestList");
static QString TL_LOAD   = QStringLiteral("LoadTestList");
static QString TL_APPEND = QStringLiteral("AppendTestList");
static QString TL_IMPORT = QStringLiteral("ImportFromFile");
static QString TL_SAVE   = QStringLiteral("SaveTestList");
static QString TL_EXPORT = QStringLiteral("ExportHMLintoText");
// Folder Selection
static QString RESOLVE_MACROS     = QStringLiteral("ResolveMacros");
static QString SET_CURRENT_FOLDER = QStringLiteral("SetCurrentFolder");
static QString INCLUDE_SUBFOLDERS = QStringLiteral("IncludeSubfolders");
static QString USE_LINKS          = QStringLiteral("UseLinks");
// Folder Modification
static QString CREATE_FOLDER              = QStringLiteral("CreateFolder");
static QString SET_FOLDER_VARIABLE        = QStringLiteral("SetFolderVariable");
static QString SET_FOLDER_AGENT           = QStringLiteral("SetFolderAgent");
static QString COPY_FOLDER                = QStringLiteral("CopyFolder");
static QString COPY_TEST                  = QStringLiteral("CopyTest");
static QString COPY_TEST_BY_ID            = QStringLiteral("CopyTestByID");
static QString COPY_ALL_TESTS             = QStringLiteral("CopyAllTests");
static QString COPY_INTO_SELECTED_FOLDERS = QStringLiteral("CopyIntoSelectedFolders");
// Manipulation with tests
static QString REFRESH_ALL                  = QStringLiteral("RefreshAll");
static QString RESET_ALL                    = QStringLiteral("ResetAll");
static QString DISABLE_ALL_TESTS            = QStringLiteral("DisableAllTests");
static QString ENABLE_ALL_TESTS             = QStringLiteral("EnableAllTests");
static QString DISABLE_TEST                 = QStringLiteral("DisableTest");
static QString ENABLE_TEST                  = QStringLiteral("EnableTest");
static QString REFRESH_TEST                 = QStringLiteral("RefreshTest");
static QString RESET_TEST                   = QStringLiteral("ResetTest");
static QString PAUSE_TEST                   = QStringLiteral("PauseTest");
static QString RESUME_TEST                  = QStringLiteral("ResumeTest");
static QString SET_TEST_PARAM               = QStringLiteral("SetTestParam");
static QString REPLACE_TEST_PARAM           = QStringLiteral("ReplaceTestParam");
static QString ACK_TEST_STATUS              = QStringLiteral("AckTestStatus");
static QString RESET_ACKNOWLEDGEMENTS       = QStringLiteral("ResetAcknowledgements");
static QString RESET_RECURRENCES_TEST       = QStringLiteral("ResetRecurrencesTest");
static QString RESET_RECURRENCES_ALL        = QStringLiteral("ResetRecurrencesAll");
static QString RESET_EVENT_LOG_REF_POINT    = QStringLiteral("ResetEventLogRefPoint");
static QString DISABLE_TEST_BY_ID           = QStringLiteral("DisableTestByID");
static QString ENABLE_TEST_BY_ID            = QStringLiteral("EnableTestByID");
static QString REFRESH_TEST_BY_ID           = QStringLiteral("RefreshTestByID");
static QString REFRESH_IRREGULAR_TEST_BY_ID = QStringLiteral("RefreshIrregularTestByID");
static QString RESET_TEST_BY_ID             = QStringLiteral("ResetTestByID");
static QString PAUSE_TEST_BY_ID             = QStringLiteral("PauseTestByID");
static QString RESUME_TEST_BY_ID            = QStringLiteral("ResumeTestByID");
static QString ACK_TEST_STATUS_BY_ID        = QStringLiteral("AckTestStatusbyID");
static QString RESET_ACKNOWLEDGEMENTS_BY_ID = QStringLiteral("ResetAcknowledgementsByID");
static QString SET_TEST_PARAM_BY_ID         = QStringLiteral("SetTestParamByID");
static QString REPLACE_TEST_PARAM_BY_ID     = QStringLiteral("ReplaceTestParamByID");
// Global Variable Commands
static QString SET_USER_VARIABLE            = QStringLiteral("SetUserVariable");
static QString SAVE_USER_VARIABLES          = QStringLiteral("SaveUserVariables");
static QString LOAD_USER_VARIABLES          = QStringLiteral("LoadUserVariables");
// Other
static QString FLUSH_COMMON_LOG             = QStringLiteral("FlushCommonLog");
static QString FLUSH_PRIVATE_LOG            = QStringLiteral("FlushPrivateLogs");
static QString CREATE_REPORT                = QStringLiteral("CreateReport");
static QString START_PROGRAM                = QStringLiteral("StartProgram");
static QString EXECUTE_PROGRAM              = QStringLiteral("ExecuteProgram");
static QString ENABLE_ALERTS                = QStringLiteral("EnableAlerts");
static QString DISABLE_ALERTS               = QStringLiteral("DisableAlerts");
static QString PAUSE_ALERTS                 = QStringLiteral("PauseAlerts");
static QString PAUSE_MONITOR                = QStringLiteral("PauseMonitor");
static QString STOP_MONITOR                 = QStringLiteral("StopMonitor");
static QString START_MONITOR                = QStringLiteral("StartMonitor");
static QString QUIT_MONITOR                 = QStringLiteral("QuitMonitor");

static QString YES = QStringLiteral("Yes");
static QString NO  = QStringLiteral("No");

class HMScriptRunner : public QObject
{
    Q_OBJECT

    HMListService *m_HML;
    QString        m_FileName;
    QStringList    m_Errors;
    QStringList    m_Script;
    // options
    bool           m_ResolveMacros;
    TNode         *m_CurrentFolder;
    bool           m_IncludeSubfolders;
    bool           m_UseLinks;

public:
    explicit HMScriptRunner(HMListService *hml, QString &fileName, QObject *parent = 0);

    bool run();
    QStringList scriptErrors() { return m_Errors; }
signals:

public slots:

private:
    bool loadScript();
    QStringList parseCmd(const QString &cmd);
    bool checkParams(const int num, const QStringList &cmdList, const int maxParams);
    bool runCmd(const int num, const QString &cmd);
// TestList operations
    bool runNewTestList(const int num, const QString &cmdLine);
    bool runLoadTestList(const int num, const QString &cmdLine);
    bool runAppendTestList(const int num, const QString &cmdLine);
    bool runImportFromFile(const int num, const QString &cmdLine);
    bool runSaveTestList(const int num, const QString &cmdLine);
    bool runExportHmlIntoText(const int num, const QString &cmdLine);
// Folder Selection
    bool runResolveMacros(const int num, const QString &cmdLine);
    bool runSetCurrentFolder(const int num, const QString &cmdLine);
    bool runIncludeSubfolders(const int num, const QString &cmdLine);
    bool runUseLinks(const int num, const QString &cmdLine);
// Folder Modification
    bool runCreateFolder(const int num, const QString &cmdLine);
    bool runSetFolderVariable(const int num, const QString &cmdLine);       //! TODO
    bool runSetFolderAgent(const int num, const QString &cmdLine);          //! TODO
    bool runCopyFolder(const int num, const QString &cmdLine);              //! TODO
    bool runCopyTest(const int num, const QString &cmdLine);                //! TODO
    bool runCopyTestByID(const int num, const QString &cmdLine);            //! TODO
    bool runCopyAllTests(const int num, const QString &cmdLine);            //! TODO
    bool runCopyIntoSelectedFolders(const int num, const QString &cmdLine); //! TODO
// Manipulation with tests
    bool runRefreshAll(const int num, const QString &cmdLine);                //! TODO
    bool runResetAll(const int num, const QString &cmdLine);                  //! TODO
    bool runDisableAllTests(const int num, const QString &cmdLine);           //! TODO
    bool runEnableAllTests(const int num, const QString &cmdLine);            //! TODO
    bool runDisableTest(const int num, const QString &cmdLine);               //! TODO
    bool runEnableTest(const int num, const QString &cmdLine);                //! TODO
    bool runRefreshTest(const int num, const QString &cmdLine);               //! TODO
    bool runResetTest(const int num, const QString &cmdLine);                 //! TODO
    bool runPauseTest(const int num, const QString &cmdLine);                 //! TODO
    bool runResumeTest(const int num, const QString &cmdLine);                //! TODO
    bool runSetTestParam(const int num, const QString &cmdLine);              //! TODO
    bool runReplaceTestParam(const int num, const QString &cmdLine);          //! TODO
    bool runAckTestStatus(const int num, const QString &cmdLine);             //! TODO
    bool runResetAcknowledgements(const int num, const QString &cmdLine);     //! TODO
    bool runResetRecurrencesTest(const int num, const QString &cmdLine);      //! TODO
    bool runResetRecurrencesAll(const int num, const QString &cmdLine);       //! TODO
    bool runResetEventLogRefPoint(const int num, const QString &cmdLine);     //! TODO
    bool runDisableTestByID(const int num, const QString &cmdLine);           //! TODO
    bool runEnableTestByID(const int num, const QString &cmdLine);            //! TODO
    bool runRefreshTestByID(const int num, const QString &cmdLine);           //! TODO
    bool runRefreshIrregularTestByID(const int num, const QString &cmdLine);  //! TODO
    bool runResetTestByID(const int num, const QString &cmdLine);             //! TODO
    bool runPauseTestByID(const int num, const QString &cmdLine);             //! TODO
    bool runResumeTestByID(const int num, const QString &cmdLine);            //! TODO
    bool runAckTestStatusbyID(const int num, const QString &cmdLine);         //! TODO
    bool runResetAcknowledgementsByID(const int num, const QString &cmdLine); //! TODO
    bool runSetTestParamByID(const int num, const QString &cmdLine);          //! TODO
    bool runReplaceTestParamByID(const int num, const QString &cmdLine);      //! TODO
// Global Variable Commands
    bool runSetUserVariable(const int num, const QString &cmdLine);   //! TODO
    bool runSaveUserVariables(const int num, const QString &cmdLine); //! TODO
    bool runLoadUserVariables(const int num, const QString &cmdLine); //! TODO
// Other
    bool runFlushCommonLog(const int num, const QString &cmdLine);   //! TODO
    bool runFlushPrivateLogs(const int num, const QString &cmdLine); //! TODO
    bool runCreateReport(const int num, const QString &cmdLine);     //! TODO
    bool runStartProgram(const int num, const QString &cmdLine);     //! TODO
    bool runExecuteProgram(const int num, const QString &cmdLine);   //! TODO
    bool runEnableAlerts(const int num, const QString &cmdLine);     //! TODO
    bool runDisableAlerts(const int num, const QString &cmdLine);    //! TODO
    bool runPauseAlerts(const int num, const QString &cmdLine);      //! TODO
    bool runPauseMonitor(const int num, const QString &cmdLine);     //! TODO
    bool runStopMonitor(const int num, const QString &cmdLine);      //! TODO
    bool runStartMonitor(const int num, const QString &cmdLine);     //! TODO
    bool runQuitMonitor(const int num, const QString &cmdLine);

};

} // namespace SDPO

#endif // HMSCRIPTRUNNER_H
