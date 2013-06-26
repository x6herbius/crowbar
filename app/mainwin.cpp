#include "mainwin.h"
#include <QMessageBox>
#include <QPluginLoader>
#include <QMenuBar>
#include <QLabel>
#include <QMdiArea>
#include <QDir>
#include <QStatusBar>
#include <QApplication>
#include <QWindowList>
#include <QWindow>
#include "globals.h"
#include "commandlineparser.h"
#include "logwindow.h"

MainWin::MainWin()
{
    setMinimumSize(320, 240);   // We don't want to go smaller than this.
    resize(800, 600);           // Set default size.

    // Create menu actions and menu bar.
    CreateMenuActions();
    CreateMenuBar();

    // Set up status bar.
    SetUpStatusBar();
}

MainWin::~MainWin()
{
}

// Creates menu actions on startup.
void MainWin::CreateMenuActions()
{
    // Set exit action to close the main window.
    m_pActFileExit = new QAction(tr("E&xit"), this);
    m_pActFileExit->setShortcuts(QKeySequence::Quit);
    connect(m_pActFileExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Set "about" action to bring up the "about" window.
    m_pActHelpAbout = new QAction(tr("About &Qt"), this);
    connect(m_pActHelpAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Set log window action to bring up the log window.
    m_pActShowLogWindow = new QAction(tr("&Log window"), this);
    //m_pActShowLogWindow->setShortcuts(*m_keyShowLogWindow);   // TODO: Get custom shortcut working for this (shift-tab?)
    connect(m_pActShowLogWindow, SIGNAL(triggered()), g_pLog, SLOT(showAndRaise()));
}

// Creates menu bar on startup.
void MainWin::CreateMenuBar()
{
    // File menu
    m_pFileMenu = menuBar()->addMenu(tr("&File"));
    m_pFileMenu->addAction(m_pActFileExit);

    // Debug menu
    m_pDebugMenu = menuBar()->addMenu(tr("&Debug"));
    m_pDebugMenu->addAction(m_pActShowLogWindow);
    //m_pDebugMenu->setVisible(g_pCmdLine->Debugging());
    m_pDebugMenu->menuAction()->setVisible(DEBUGGING);

    // Help menu
    m_pHelpMenu = menuBar()->addMenu(tr("&Help"));
    m_pHelpMenu->addAction(m_pActHelpAbout);
}

// Sets up status bar.
void MainWin::SetUpStatusBar()
{
    // The status bar is automatically created by the first call to statusBar().
    statusBar()->setSizeGripEnabled(true);
}
