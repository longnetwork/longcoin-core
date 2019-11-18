// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletview.h"

#include "addressbookpage.h"
#include "askpassphrasedialog.h"
#include "bitcoingui.h"
#include "clientmodel.h"
#include "guiutil.h"
#include "optionsmodel.h"
#include "overviewpage.h"
#include "platformstyle.h"
#include "receivecoinsdialog.h"
#include "sendcoinsdialog.h"
#include "signverifymessagedialog.h"
#include "transactiontablemodel.h"
#include "transactionview.h"
#include "walletmodel.h"

#include "ui_interface.h"

#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QProgressDialog>
#include <QPushButton>
#include <QVBoxLayout>

WalletView::WalletView(const PlatformStyle *platformStyle, QWidget *parent):
    QStackedWidget(parent),
    clientModel(0),
    walletModel(0),
    platformStyle(platformStyle)
{
    // Create tabs
    overviewPage = new OverviewPage(platformStyle);

    transactionsPage1 = new QWidget(this);
        transactionsPage2 = new QWidget(this);
/*
        transactionsPage3 = new QWidget(this);
        transactionsPage4 = new QWidget(this);
*/    
    QVBoxLayout *vbox1 = new QVBoxLayout();
        QVBoxLayout *vbox2 = new QVBoxLayout();
/*
        QVBoxLayout *vbox3 = new QVBoxLayout();
        QVBoxLayout *vbox4 = new QVBoxLayout();
*/
    QHBoxLayout *hbox_buttons1 = new QHBoxLayout();
        QHBoxLayout *hbox_buttons2 = new QHBoxLayout();
/*
        QHBoxLayout *hbox_buttons3 = new QHBoxLayout();
        QHBoxLayout *hbox_buttons4 = new QHBoxLayout();
*/
    transactionView1 = new TransactionView(platformStyle, this);
        transactionView2 = new TransactionView(platformStyle, this);
/*
        transactionView3 = new TransactionView(platformStyle, this);
        transactionView4 = new TransactionView(platformStyle, this);
*/
    vbox1->addWidget(transactionView1);
        vbox2->addWidget(transactionView2);
/*
        vbox3->addWidget(transactionView3);
        vbox4->addWidget(transactionView4);
*/
    QPushButton *exportButton1 = new QPushButton(tr("&Export"), this);
        QPushButton *exportButton2 = new QPushButton(tr("&Export"), this);
/*
        QPushButton *exportButton3 = new QPushButton(tr("&Export"), this);
        QPushButton *exportButton4 = new QPushButton(tr("&Export"), this);
*/
    exportButton1->setToolTip(tr("Export the data in the current tab to a file"));
        exportButton2->setToolTip(tr("Export the data in the current tab to a file"));
/*
        exportButton3->setToolTip(tr("Export the data in the current tab to a file"));
        exportButton4->setToolTip(tr("Export the data in the current tab to a file"));
*/        
    if (platformStyle->getImagesOnButtons()) {
        exportButton1->setIcon(platformStyle->SingleColorIcon(":/icons/export"));
            exportButton2->setIcon(platformStyle->SingleColorIcon(":/icons/export"));
/*
            exportButton3->setIcon(platformStyle->SingleColorIcon(":/icons/export"));
            exportButton4->setIcon(platformStyle->SingleColorIcon(":/icons/export"));
*/
    }
    hbox_buttons1->addStretch();
        hbox_buttons2->addStretch();
/*
        hbox_buttons3->addStretch();
        hbox_buttons4->addStretch();
*/
    hbox_buttons1->addWidget(exportButton1);
        hbox_buttons2->addWidget(exportButton2);
/*
        hbox_buttons3->addWidget(exportButton3);
        hbox_buttons4->addWidget(exportButton4);
*/
    vbox1->addLayout(hbox_buttons1);
        vbox2->addLayout(hbox_buttons2);
/*
        vbox3->addLayout(hbox_buttons3);
        vbox4->addLayout(hbox_buttons4);
*/
    transactionsPage1->setLayout(vbox1);
        transactionsPage2->setLayout(vbox2);
/*
        transactionsPage3->setLayout(vbox3);
        transactionsPage4->setLayout(vbox4);
*/

    receiveCoinsPage = new ReceiveCoinsDialog(platformStyle);
    sendCoinsPage = new SendCoinsDialog(platformStyle);

    usedSendingAddressesPage = new AddressBookPage(platformStyle, AddressBookPage::ForEditing, AddressBookPage::SendingTab, this);
    usedReceivingAddressesPage = new AddressBookPage(platformStyle, AddressBookPage::ForEditing, AddressBookPage::ReceivingTab, this);

    addWidget(overviewPage);
    addWidget(transactionsPage1); addWidget(transactionsPage2); /*addWidget(transactionsPage3); addWidget(transactionsPage4);*/
    addWidget(receiveCoinsPage);
    addWidget(sendCoinsPage);

    // Clicking on a transaction on the overview pre-selects the transaction on the transaction history page
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView1, SLOT(focusTransaction(QModelIndex)));
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView2, SLOT(focusTransaction(QModelIndex)));
/*
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView3, SLOT(focusTransaction(QModelIndex)));
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView4, SLOT(focusTransaction(QModelIndex)));
*/
    // Double-clicking on a transaction on the transaction history page shows details
    connect(transactionView1, SIGNAL(doubleClicked(QModelIndex)), transactionView1, SLOT(showDetails()));
    connect(transactionView2, SIGNAL(doubleClicked(QModelIndex)), transactionView2, SLOT(showDetails()));
/*
    connect(transactionView3, SIGNAL(doubleClicked(QModelIndex)), transactionView3, SLOT(showDetails()));
    connect(transactionView4, SIGNAL(doubleClicked(QModelIndex)), transactionView4, SLOT(showDetails()));
*/
    // Clicking on "Export" allows to export the transaction list
    connect(exportButton1, SIGNAL(clicked()), transactionView1, SLOT(exportClicked()));
    connect(exportButton2, SIGNAL(clicked()), transactionView2, SLOT(exportClicked()));
/*
    connect(exportButton3, SIGNAL(clicked()), transactionView3, SLOT(exportClicked()));
    connect(exportButton4, SIGNAL(clicked()), transactionView4, SLOT(exportClicked()));     
*/
    // Pass through messages from sendCoinsPage
    connect(sendCoinsPage, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
    // Pass through messages from transactionView
    connect(transactionView1, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
    connect(transactionView2, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
/*
    connect(transactionView3, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
    connect(transactionView4, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));
*/

    connect(transactionView1, SIGNAL(replyToPushButtonClicked(QString)), this, SLOT(onReplyToPushButtonClicked(QString)));
    connect(transactionView2, SIGNAL(replyToPushButtonClicked(QString)), this, SLOT(onReplyToPushButtonClicked(QString)));
/*
    connect(transactionView3, SIGNAL(replyToPushButtonClicked(QString)), this, SLOT(onReplyToPushButtonClicked(QString)));
    connect(transactionView4, SIGNAL(replyToPushButtonClicked(QString)), this, SLOT(onReplyToPushButtonClicked(QString)));
*/
}

WalletView::~WalletView()
{
}

void WalletView::setBitcoinGUI(BitcoinGUI *gui)
{
    if (gui)
    {
        // Clicking on a transaction on the overview page simply sends you to transaction history page
//        connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), gui, SLOT(gotoHistoryPage4()));
//        connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), gui, SLOT(gotoHistoryPage3()));
//        connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), gui, SLOT(gotoHistoryPage2()));



        connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), gui, SLOT(gotoHistoryPage1()));
        // Наверно пролистает подряд....

        // Receive and report messages
        connect(this, SIGNAL(message(QString,QString,unsigned int)), gui, SLOT(message(QString,QString,unsigned int)));

        // Pass through encryption status changed signals
        connect(this, SIGNAL(encryptionStatusChanged(int)), gui, SLOT(setEncryptionStatus(int)));

        // Pass through transaction notifications
        connect(this, SIGNAL(incomingTransaction(QString,int,CAmount,QString,QString,QString,QString)), gui, SLOT(incomingTransaction(QString,int,CAmount,QString,QString,QString,QString)));
    }
}

void WalletView::setClientModel(ClientModel *clientModel)
{
    this->clientModel = clientModel;

    overviewPage->setClientModel(clientModel);
    sendCoinsPage->setClientModel(clientModel);
}

void WalletView::setWalletModel(WalletModel *walletModel)
{
    this->walletModel = walletModel;

    // Put transaction list in tabs
    transactionView1->setModel(walletModel);
        transactionView2->setModel(walletModel);
/*
        transactionView3->setModel(walletModel);
        transactionView4->setModel(walletModel);
*/
    overviewPage->setWalletModel(walletModel);
    receiveCoinsPage->setModel(walletModel);
    sendCoinsPage->setModel(walletModel);
    usedReceivingAddressesPage->setModel(walletModel->getAddressTableModel());
    usedSendingAddressesPage->setModel(walletModel->getAddressTableModel());

    if (walletModel)
    {
        // Receive and pass through messages from wallet model
        connect(walletModel, SIGNAL(message(QString,QString,unsigned int)), this, SIGNAL(message(QString,QString,unsigned int)));

        // Handle changes in encryption status
        connect(walletModel, SIGNAL(encryptionStatusChanged(int)), this, SIGNAL(encryptionStatusChanged(int)));
        updateEncryptionStatus();

        // Balloon pop-up for new transaction
        connect(walletModel->getTransactionTableModel(), SIGNAL(rowsInserted(QModelIndex,int,int)),
                this, SLOT(processNewTransaction(QModelIndex,int,int)));

        // Ask for passphrase if needed
        connect(walletModel, SIGNAL(requireUnlock()), this, SLOT(unlockWallet()));

        // Show progress dialog
        connect(walletModel, SIGNAL(showProgress(QString,int)), this, SLOT(showProgress(QString,int)));
    }
}

void WalletView::processNewTransaction(const QModelIndex& parent, int start, int /*end*/)
{
    // Prevent balloon-spam when initial block download is in progress
    if (!walletModel || !clientModel || clientModel->inInitialBlockDownload())
        return;

    TransactionTableModel *ttm = walletModel->getTransactionTableModel();
    if (!ttm || ttm->processingQueuedTransactions())
        return;

    QString date = ttm->index(start, TransactionTableModel::Date, parent).data().toString();
    qint64 amount = ttm->index(start, TransactionTableModel::Amount, parent).data(Qt::EditRole).toULongLong();
    QString type = ttm->index(start, TransactionTableModel::Type, parent).data().toString();
    QModelIndex index = ttm->index(start, 0, parent);
    QString address = ttm->data(index, TransactionTableModel::AddressRoleTo).toString(); // FixMe for AddressRoleFrom
    QString label = ttm->data(index, TransactionTableModel::LabelRoleTo).toString(); // FixMe for LabelRoleFrom
    QString pubKeyHex = ttm->data(index, TransactionTableModel::PubKeyHexRole).toString();


    Q_EMIT incomingTransaction(date, walletModel->getOptionsModel()->getDisplayUnit(), amount, type, address, label, pubKeyHex);
}

void WalletView::gotoOverviewPage()
{
    setCurrentWidget(overviewPage);
}

void WalletView::gotoHistoryPage1()
{
    setCurrentWidget(transactionsPage1);
}
void WalletView::gotoHistoryPage2()
{
    setCurrentWidget(transactionsPage2);
}
/*
void WalletView::gotoHistoryPage3()
{
    setCurrentWidget(transactionsPage3);
}
void WalletView::gotoHistoryPage4()
{
    setCurrentWidget(transactionsPage4);
}
*/
void WalletView::gotoReceiveCoinsPage()
{
    setCurrentWidget(receiveCoinsPage);
}

void WalletView::gotoSendCoinsPage(QString addr)
{
    setCurrentWidget(sendCoinsPage);

    if (!addr.isEmpty())
        sendCoinsPage->setAddress(addr);
}
void WalletView::onReplyToPushButtonClicked(const QString &pubKeyHex)
{
    setCurrentWidget(sendCoinsPage);
    if (!pubKeyHex.isEmpty())
        sendCoinsPage->setLONGMessage(pubKeyHex);
}

void WalletView::gotoSignMessageTab(QString addr)
{
    // calls show() in showTab_SM()
    SignVerifyMessageDialog *signVerifyMessageDialog = new SignVerifyMessageDialog(platformStyle, this);
    signVerifyMessageDialog->setAttribute(Qt::WA_DeleteOnClose);
    signVerifyMessageDialog->setModel(walletModel);
    signVerifyMessageDialog->showTab_SM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_SM(addr);
}

void WalletView::gotoVerifyMessageTab(QString addr)
{
    // calls show() in showTab_VM()
    SignVerifyMessageDialog *signVerifyMessageDialog = new SignVerifyMessageDialog(platformStyle, this);
    signVerifyMessageDialog->setAttribute(Qt::WA_DeleteOnClose);
    signVerifyMessageDialog->setModel(walletModel);
    signVerifyMessageDialog->showTab_VM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_VM(addr);
}

bool WalletView::handlePaymentRequest(const SendCoinsRecipient& recipient)
{
    return sendCoinsPage->handlePaymentRequest(recipient);
}

void WalletView::showOutOfSyncWarning(bool fShow)
{
    overviewPage->showOutOfSyncWarning(fShow);
}

void WalletView::updateEncryptionStatus()
{
    Q_EMIT encryptionStatusChanged(walletModel->getEncryptionStatus());
}

void WalletView::encryptWallet(bool status)
{
    if(!walletModel)
        return;
    AskPassphraseDialog dlg(status ? AskPassphraseDialog::Encrypt : AskPassphraseDialog::Decrypt, this);
    dlg.setModel(walletModel);
    dlg.exec();

    updateEncryptionStatus();
}

void WalletView::backupWallet()
{
    QString filename = GUIUtil::getSaveFileName(this,
        tr("Backup Wallet"), QString(),
        tr("Wallet Data (*.dat)"), NULL);

    if (filename.isEmpty())
        return;

    if (!walletModel->backupWallet(filename)) {
        Q_EMIT message(tr("Backup Failed"), tr("There was an error trying to save the wallet data to %1.").arg(filename),
            CClientUIInterface::MSG_ERROR);
        }
    else {
        Q_EMIT message(tr("Backup Successful"), tr("The wallet data was successfully saved to %1.").arg(filename),
            CClientUIInterface::MSG_INFORMATION);
    }
}

void WalletView::changePassphrase()
{
    AskPassphraseDialog dlg(AskPassphraseDialog::ChangePass, this);
    dlg.setModel(walletModel);
    dlg.exec();
}

void WalletView::unlockWallet()
{
    if(!walletModel)
        return;
    // Unlock wallet when requested by wallet model
    if (walletModel->getEncryptionStatus() == WalletModel::Locked)
    {
        AskPassphraseDialog dlg(AskPassphraseDialog::Unlock, this);
        dlg.setModel(walletModel);
        dlg.exec();
    }
}

void WalletView::usedSendingAddresses()
{
    if(!walletModel)
        return;

    usedSendingAddressesPage->show();
    usedSendingAddressesPage->raise();
    usedSendingAddressesPage->activateWindow();
}

void WalletView::usedReceivingAddresses()
{
    if(!walletModel)
        return;

    usedReceivingAddressesPage->show();
    usedReceivingAddressesPage->raise();
    usedReceivingAddressesPage->activateWindow();
}

void WalletView::showProgress(const QString &title, int nProgress)
{
    if (nProgress == 0)
    {
        progressDialog = new QProgressDialog(title, "", 0, 100);
        progressDialog->setWindowModality(Qt::ApplicationModal);
        progressDialog->setMinimumDuration(0);
        progressDialog->setCancelButton(0);
        progressDialog->setAutoClose(false);
        progressDialog->setValue(0);
    }
    else if (nProgress == 100)
    {
        if (progressDialog)
        {
            progressDialog->close();
            progressDialog->deleteLater();
        }
    }
    else if (progressDialog)
        progressDialog->setValue(nProgress);
}
