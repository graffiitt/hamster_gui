#include "programmeditorwidget.h"
#include "ui_programmeditorwidget.h"

ProgrammEditorWidget::ProgrammEditorWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammEditorWidget)
{
    ui->setupUi(this);

    commentCmd = new CommentCommand();
    emptyCmd = new EmptyCommand();
    mathCmd = new MathCommand();
    callCmd = new CallCommand();
    jmpCmd = new JumpCommand();
    waitCmd = new WaitCommand();
    moveCmd = new MoveCommand();
    ifCmd = new IfCommand();
    ioCmd = new IoCommand();

    programm = new Programm();
    programmModel = new ProgrammModel(programm);
    ui->programmView->setModel(programmModel);
    jsonLoad = new JSONmodule();
}

ProgrammEditorWidget::~ProgrammEditorWidget()
{
    delete ui;
    delete programmModel;
    for (int i = programm->size(); i > 0; i--)
        delete programm->takeAt(i - 1);
    delete programm;
    delete commentCmd;
    delete emptyCmd;
    delete mathCmd;
    delete callCmd;
    delete jmpCmd;
    delete waitCmd;
    delete moveCmd;
    delete ifCmd;
    delete ioCmd;
    delete jsonLoad;
}

void ProgrammEditorWidget::openProgramm(QString path)
{
    programmModel->updateProgramm(jsonLoad->openFile(path));
}

void ProgrammEditorWidget::createNewProgramm(QString path)
{
    jsonLoad->createProgramm(path);
    this->openProgramm(path);
    QModelIndex idx = ui->programmView->currentIndex();
    emptyCmd = new EmptyCommand();
    programmModel->addComand(idx, emptyCmd);
}

void ProgrammEditorWidget::saveProgramm(QString path)
{
    jsonLoad->saveFile(programm, path);
}

void ProgrammEditorWidget::on_moveButton_clicked()
{
    if (ui->toolEditWidget->currentIndex() != 0)
    {
        ui->toolEditWidget->setCurrentIndex(0);
        ui->addButton->setEnabled(true);
    }
}

void ProgrammEditorWidget::on_logicButton_clicked()
{
    if (ui->toolEditWidget->currentIndex() != 1)
    {
        ui->toolEditWidget->setCurrentIndex(1);
        ui->addButton->setEnabled(false);
    }
}

void ProgrammEditorWidget::on_mathButton_clicked()
{
    if (ui->toolEditWidget->currentIndex() != 2)
    {
        ui->toolEditWidget->setCurrentIndex(2);
        ui->addButton->setEnabled(true);
    }
}

void ProgrammEditorWidget::on_addButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();

    switch (ui->toolEditWidget->currentIndex())
    {
    case 0:
    {
        programmModel->addComand(idx, moveCmd);
        moveCmd = new MoveCommand();
        break;
    }
    case 2:
    {
        programmModel->addComand(idx, mathCmd);
        mathCmd = new MathCommand();
        break;
    }
    }
}

void ProgrammEditorWidget::on_addLineButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->addComand(idx, emptyCmd);
    emptyCmd = new EmptyCommand();
}

void ProgrammEditorWidget::on_deleteButton_clicked()
{
    programmModel->deleteCommand(ui->programmView->currentIndex());
}

void ProgrammEditorWidget::on_programmView_clicked(const QModelIndex &index)
{
    switch (programmModel->getId(index))
    {
    case Command::Comment:
    {
        this->on_logicButton_clicked();

        QString dt = programmModel->getData(index, "data").toString();
        ui->commentLineEdit->setText(dt);
        break;
    }
    case Command::Call:
    {
        break;
    }
    case Command::Empty:
    {
        break;
    }
    case Command::If:
    {
        this->on_logicButton_clicked();

        break;
    }
    case Command::Jump:
    {
        this->on_logicButton_clicked();

        ui->lblComboBox->setCurrentIndex(programmModel->getData(index, "mode").toInt());
        ui->lblSpinBox->setValue(programmModel->getData(index, "lbl").toInt());
        break;
    }
    case Command::Math:
    {
        this->on_mathButton_clicked();
        this->updateUIMathReg(index);
        this->updateUINumbers(index);
        break;
    }
    case Command::Point:
    {
        this->on_moveButton_clicked();
        ui->moveTypeBox->setCurrentIndex(programmModel->getData(index, "moveType").toInt());
        ui->moveTypePointBox->setCurrentIndex(programmModel->getData(index, "pointType").toInt());
        ui->movePoseRegBox->setValue(programmModel->getData(index, "numberRegister").toInt());
        ui->moveSpeedBox->setValue(programmModel->getData(index, "speed").toInt());
        ui->moveAccBox->setValue(programmModel->getData(index, "acc").toInt());

        QJsonObject obj = programmModel->getData(index, "point").toObject();
        if (obj["coordType"].toInt() == CoordType::joint)
        {
            ui->moveDataBox_1->setValue(obj["j1"].toInt());
            ui->moveDataBox_2->setValue(obj["j2"].toInt());
            ui->moveDataBox_3->setValue(obj["j3"].toInt());
            ui->moveDataBox_4->setValue(obj["j4"].toInt());
        }
        break;
    }
    case Command::Wait:
    {
        this->on_logicButton_clicked();
        ui->waitBox->setCurrentIndex(programmModel->getData(index, "waitType").toInt());
        if (programmModel->getData(index, "waitType").toInt() == 0)
            ui->waitSpinBox->setValue(programmModel->getData(index, "time").toInt());
        else
            ui->waitSpinBox->setValue(programmModel->getData(index, "pinIn").toInt());

        break;
    }
    case Command::Io:
    {
        this->on_logicButton_clicked();
        // ui->ioCheckBox->
        ui->ioComboBox->setCurrentIndex(programmModel->getData(index, "type").toInt());
        ui->ioSpinBox->setValue(programmModel->getData(index, "pin").toInt());
        break;
    }
    }
}

void ProgrammEditorWidget::on_moveOverwriteButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    QJsonObject point;
    point.insert("coordType", CoordType::joint);
    point.insert("j1", ui->moveDataBox_1->value());
    point.insert("j2", ui->moveDataBox_2->value());
    point.insert("j3", ui->moveDataBox_3->value());
    point.insert("j4", ui->moveDataBox_4->value());

    programmModel->setData(point, "point", Command::Point, idx);
}

void ProgrammEditorWidget::on_moveTypePointBox_activated(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "pointType", Command::Point, idx);
}

void ProgrammEditorWidget::on_moveTypeBox_activated(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "moveType", Command::Point, idx);
}

void ProgrammEditorWidget::on_moveAccBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "acc", Command::Point, idx);
}

void ProgrammEditorWidget::on_moveSpeedBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "speed", Command::Point, idx);
}

void ProgrammEditorWidget::on_movePoseRegBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "numberRegister", Command::Point, idx);
}

void ProgrammEditorWidget::on_commentButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    commentCmd = new CommentCommand();
    programmModel->addComand(idx, commentCmd);

    if (idx.isValid())
    {
        QString dt = programmModel->getData(idx, "data").toString();
        ui->commentLineEdit->setText(dt);
    }
}

void ProgrammEditorWidget::on_commentLineEdit_textChanged(const QString &arg1)
{
    programmModel->setData(arg1, "data", Command::Comment, ui->programmView->currentIndex());
}

void ProgrammEditorWidget::on_regOutBox_currentIndexChanged(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index ? 2 : 1, "regOutType", Command::Math, idx);
    index ? ui->registerBox_2->setEnabled(true) : ui->registerBox_2->setEnabled(false);
    this->updateUIMathReg(idx);
}

void ProgrammEditorWidget::on_registerBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();

    switch (programmModel->getData(idx, "regOutType").toInt())
    {
    case 1:
    {
        programmModel->setData(arg1, "regOut", Command::Math, idx);
        break;
    }
    case 2:
    {
        programmModel->setData(arg1, "poseReg", Command::Math, idx);
        break;
    }
    }
}

void ProgrammEditorWidget::on_registerBox_2_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "poseRegItem", Command::Math, idx);
}

void ProgrammEditorWidget::on_typeComboBox_2_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "itemType_2", Command::Math, idx);
    if (index == 2 && programmModel->getId(idx) == Command::Math)
        ui->itemPoseReg_2->setEnabled(true);
    else
        ui->itemPoseReg_2->setEnabled(false);
}

void ProgrammEditorWidget::on_typeComboBox_1_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "itemType_1", Command::Math, idx);
    if (index == 2 && programmModel->getId(idx) == Command::Math)
        ui->itemPoseReg_1->setEnabled(true);
    else
        ui->itemPoseReg_1->setEnabled(false);
}

void ProgrammEditorWidget::on_operatorComboBox_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "operator", Command::Math, idx);
}

void ProgrammEditorWidget::on_firstNumBox_valueChanged(int arg1)
{
    this->updateRegItem(arg1, 1, Command::Math);
}

void ProgrammEditorWidget::on_itemPoseReg_1_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "poseRegItem_1", Command::Math, idx);
}

void ProgrammEditorWidget::on_itemPoseReg_2_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "poseRegItem_2", Command::Math, idx);
}

void ProgrammEditorWidget::on_secondNumBox_valueChanged(int arg1)
{
    this->updateRegItem(arg1, 2, Command::Math);
}

void ProgrammEditorWidget::updateUIMathReg(QModelIndex index)
{
    // QModelIndex index = ui->programmView->currentIndex();

    int regType = programmModel->getData(index, "regOutType").toInt() - 1;
    int regNum = regType ? programmModel->getData(index, "poseReg").toInt()
                         : programmModel->getData(index, "regOut").toInt();

    ui->registerBox_2->setValue(programmModel->getData(index, "poseRegItem").toInt());
    ui->registerBox->setValue(regNum);
    ui->regOutBox->setCurrentIndex(regType);
}

void ProgrammEditorWidget::updateUINumbers(QModelIndex index)
{
    int num;
    ui->typeComboBox_1->setCurrentIndex(programmModel->getData(index, "itemType_1").toInt());
    switch (programmModel->getData(index, "itemType_1").toInt())
    {
    case 0:
    {
        num = programmModel->getData(index, "number_1").toInt();
        break;
    }
    case 1:
    {
        num = programmModel->getData(index, "register_1").toInt();
        break;
    }
    case 2:
    {
        num = programmModel->getData(index, "poseReg_1").toInt();
        break;
    }
    }
    ui->firstNumBox->setValue(num);
    ui->typeComboBox_2->setCurrentIndex(programmModel->getData(index, "itemType_2").toInt());

    switch (programmModel->getData(index, "itemType_2").toInt())
    {
    case 0:
    {
        num = programmModel->getData(index, "number_2").toInt();
        break;
    }
    case 1:
    {
        num = programmModel->getData(index, "register_2").toInt();
        break;
    }
    case 2:
    {
        num = programmModel->getData(index, "poseReg_2").toInt();
        break;
    }
    }

    ui->secondNumBox->setValue(num);
    ui->operatorComboBox->setCurrentIndex(programmModel->getData(index, "operator").toInt());
    ui->itemPoseReg_1->setValue(programmModel->getData(index, "poseRegItem_1").toInt());
    ui->itemPoseReg_2->setValue(programmModel->getData(index, "poseRegItem_2").toInt());
}

void ProgrammEditorWidget::updateRegItem(int arg1, int number, Command id)
{
    QModelIndex idx = ui->programmView->currentIndex();

    switch (programmModel->getData(idx, QString("itemType_%1").arg(number)).toInt())
    {
    case 0:
    {
        programmModel->setData(arg1, QString("number_%1").arg(number), id, idx);
        break;
    }
    case 1:
    {
        programmModel->setData(arg1, QString("register_%1").arg(number), id, idx);
        break;
    }
    case 2:
    {
        programmModel->setData(arg1, QString("poseReg_%1").arg(number), id, idx);
        break;
    }
    case 3:
        programmModel->setData(arg1, QString("ioPin_%1").arg(number), id, idx);
        break;
    }
}

void ProgrammEditorWidget::updateLanguage()
{
    QLocale locale;
    QString path = QApplication::applicationDirPath();
    QString fileName = QString("/ProgEditorWidget_%1.qm").arg(locale.name());

    qApp->removeTranslator(&translate);
    if (translate.load(path + fileName))
    {
        qApp->installTranslator(&translate);
    }
}

void ProgrammEditorWidget::on_callButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    QString name = JSONmodule::getPathGUI(this);

    if (!name.isEmpty())
    {
        programmModel->addComand(idx, callCmd);
        programmModel->setData(name, "namePrg", Command::Call, idx);
        callCmd = new CallCommand();
    }
}

void ProgrammEditorWidget::on_lblButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->addComand(idx, jmpCmd);
    jmpCmd = new JumpCommand();
}

void ProgrammEditorWidget::on_waitButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->addComand(idx, waitCmd);
    waitCmd = new WaitCommand();
}

void ProgrammEditorWidget::on_ifButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->addComand(idx, ifCmd);
    ifCmd = new IfCommand();
}

void ProgrammEditorWidget::on_ifBeheviorBox_currentIndexChanged(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "operator", Command::If, idx);
}

void ProgrammEditorWidget::on_ifItem_1_Box_currentIndexChanged(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    if (idx.isValid())
    {
        programmModel->setData(index, "itemType_1", Command::If, idx);
        if (index == 2 && programmModel->getId(idx) == Command::If)
            ui->ifItem_1_Spin_2->setEnabled(true);
        else
            ui->ifItem_1_Spin_2->setEnabled(false);

        if (index == 3 && programmModel->getId(idx) == Command::If)
        {
            ui->ifIOstate->setEnabled(true);
            ui->ifItem_2_Box->setEnabled(false);
            ui->ifItem_2_Spin->setEnabled(false);
            ui->ifItem_2_Spin_2->setEnabled(false);
        }
        else
        {
            ui->ifIOstate->setEnabled(false);
            ui->ifItem_2_Box->setEnabled(true);
            ui->ifItem_2_Spin->setEnabled(true);
        }
    }
}

void ProgrammEditorWidget::on_ifItem_2_Box_currentIndexChanged(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    if (idx.isValid())
    {
        programmModel->setData(index, "itemType_2", Command::If, idx);
        if (index == 2 && programmModel->getId(idx) == Command::If)
            ui->ifItem_2_Spin_2->setEnabled(true);
        else
            ui->ifItem_2_Spin_2->setEnabled(false);
    }
}

void ProgrammEditorWidget::on_ifItem_1_Spin_valueChanged(int arg1)
{
    this->updateRegItem(arg1, 1, Command::If);
}

void ProgrammEditorWidget::on_ifItem_2_Spin_valueChanged(int arg1)
{
    this->updateRegItem(arg1, 2, Command::If);
}

void ProgrammEditorWidget::on_ifItem_1_Spin_2_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "poseRegItem_1", Command::If, idx);
}

void ProgrammEditorWidget::on_ifItem_2_Spin_2_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "poseRegItem_2", Command::If, idx);
}

void ProgrammEditorWidget::on_iflLblBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "jumpLBL", Command::If, idx);
}

void ProgrammEditorWidget::on_ifIOstate_stateChanged(int state)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(state, "ioPinState_1", Command::If, idx);
}

void ProgrammEditorWidget::on_ioButton_clicked()
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->addComand(idx, ioCmd);
    ioCmd = new IoCommand();
}

void ProgrammEditorWidget::on_ioComboBox_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "type", Command::Io, idx);
}

void ProgrammEditorWidget::on_ioSpinBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "pin", Command::Io, idx);
}

void ProgrammEditorWidget::on_ioCheckBox_stateChanged(int state)
{
    bool st = true;
    if (state == 0)
        st = false;
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(st, "state", Command::Io, idx);
}

void ProgrammEditorWidget::on_waitBox_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    if (!idx.isValid())
        return;
    programmModel->setData(index, "waitType", Command::Wait, idx);

    if (index == 0)
        ui->waitSpinBox->setValue(programmModel->getData(idx, "time").toInt());
    else
        ui->waitSpinBox->setValue(programmModel->getData(idx, "pinIn").toInt());
}

void ProgrammEditorWidget::on_waitSpinBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    if (!idx.isValid())
        return;
    switch (programmModel->getData(idx, "waitType").toInt())
    {
    case WaitType::timer:
    {
        programmModel->setData(arg1, "time", Command::Wait, idx);
        break;
    }
    case WaitType::ioHigh:
    case WaitType::ioLow:
    {
        programmModel->setData(arg1, "pinIn", Command::Wait, idx);
        break;
    }
    }
}

void ProgrammEditorWidget::on_lblSpinBox_valueChanged(int arg1)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(arg1, "lbl", Command::Jump, idx);
}

void ProgrammEditorWidget::on_lblComboBox_activated(int index)
{
    QModelIndex idx = ui->programmView->currentIndex();
    programmModel->setData(index, "mode", Command::Jump, idx);
}

void ProgrammEditorWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
