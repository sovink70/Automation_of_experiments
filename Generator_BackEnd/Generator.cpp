#include "Generator.h"

//Generator::Generator(QObject *parent) : QObject(parent)
//{
//    toNULL();
//}

///Стандартный конструктор, просто вызывает toNULL()
Generator::Generator()
{
    toNULL();
}

///конструктор, принимает только модель генератора и устанавливает её в переменную this->generatorModel. Перед этим также вызывает toNULL()
Generator::Generator(const std::string &new_generatorModel){
    toNULL();
    setGeneratorModel(new_generatorModel);
}

///конструктор, принимает portName, baudrate, dataBit, stopBit, parity, flowcontrol, new_generatorModel И уже вызывает SETconnect с этими параметрами. Перед этим также вызывает toNULL()
Generator::Generator(const std::string &portName, const std::string &baudrate, const std::string &dataBit, const std::string &stopBit, const std::string &parity, const std::string &flowcontrol, const std::string &new_generatorModel) //(const std::string &portName, const int &baudrate, const int &stopBit, const int &parity, const std::string &new_generatorModel)
{
    toNULL();
    SETconnect(portName, baudrate, dataBit, stopBit, parity, flowcontrol, new_generatorModel);//setConnection(portName, baudrate, stopBit, parity, new_generatorModel);
}

// ///конструктор, принимает portName ( запрашивает и определяет сам baudrate, dataBit, stopBit, parity, flowcontrol, new_generatorModel) И уже вызывает SETconnect с этими параметрами. Перед этим также вызывает toNULL()
//Generator::Generator(const std::string &portName) //(const std::string &portName, const int &baudrate, const int &stopBit, const int &parity, const std::string &new_generatorModel)
//{
//    toNULL();
//    SETconnect(portName);
//}

//не нужно пока
//Generator::Generator(QSerialPort *serial, const QString &new_generatorModel)
//{
//    toNULL();
//    QString _generatorModel = new_generatorModel.trimmed().toUpper();
//    if (_generatorModel == "DS335") {
//        if (this->ds335 == nullptr)
//            this->ds335 = new DS335(serial->portName(), serial->baudRate());
//        else
//            this->ds335->setSerial(serial);
//    }
//    if (_generatorModel == "DS345") {
//        if (this->ds345 == nullptr)
//            this->ds345 = new DS345(serial->portName(), serial->baudRate());
//        else
//            this->ds345->setSerial(serial);
//    }
//    if (_generatorModel.isEmpty() ||
//        _generatorModel == "AUTO")
//        autoSetGeneratorModel(serial);
//}

// ///∂
//Generator::Generator(DS335 *new_ds335)
//{
//    toNULL();
//    setDS335(new_ds335);
//}

// ///∂
//Generator::Generator(DS345 *new_ds345)
//{
//    toNULL();
//    setDS345(new_ds345);
//}

///деструктор
Generator::~Generator()
{
    this->generatorModel.clear();
    if (this->ds335 != nullptr)
        this->ds335->~DS335();
    delete this->ds335;
    if (this->ds345 != nullptr)
        this->ds345->~DS345();
    delete this->ds345;
    if (this->srs != nullptr)
        this->srs->~SRS();
    delete this->srs;

    this->ds335 = nullptr;
    this->ds345 = nullptr;
    this->srs = nullptr;
}

///устанавливает указатели обоих объектов (DS335 и DS345) на nullptr и запускает ф-цию init()
void Generator::toNULL()
{
    if (this->ds335 != nullptr) {
        this->ds335 = nullptr;
    }
    if (this->ds345 != nullptr) {
        this->ds345 = nullptr;
    }
    if (this->srs != nullptr) {
        this->srs = nullptr;
    }

    init();

    return;
}

///если указатель SRS установлен на nullptr (то есть по сути не создан SerialPort), то создает new SRS()
void Generator::init()
{
    if (this->srs == nullptr)
        this->srs = new SRS();

//тут никакие коннекты не нужны, они внутри конструкторов
//    if (this->srs != nullptr) {
//        connect(this->srs,   SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
//        connect(this->srs,   SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
//        connect(this->srs,   SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
//        connect(this->srs,   SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
//    }
//    if (this->ds335 != nullptr) {
//        connect(this->ds335, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
//        connect(this->ds335, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
//        connect(this->ds335, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
//        connect(this->ds335, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
//    }
//    if (this->ds345 != nullptr) {
//        connect(this->ds345, SIGNAL(errorSignal(QString)),    this, SLOT(catchErrorSignal(QString)),    Qt::DirectConnection);
//        connect(this->ds345, SIGNAL(responseSignal(QString)), this, SLOT(catchResponseSignal(QString)), Qt::DirectConnection);
//        connect(this->ds345, SIGNAL(commandSignal(QString)),  this, SLOT(catchCommandSignal(QString)),  Qt::DirectConnection);
//        connect(this->ds345, SIGNAL(timeoutSignal(QString)),  this, SLOT(catchTimeoutSignal(QString)),  Qt::DirectConnection);
//    }
    return;
}

///определяет текущее состояние генератора, возвращает структуру struct Generator_State
Generator_State Generator::getState()
{
    Generator_State current_state;

    current_state.model = this->generatorModel;

    if (workWithAmplitude())
        current_state.amplitude = getAmplitude("VR");
    if (workWithOffset())
        current_state.offset = getOffset();
    if (workWithFrequency())
        current_state.frequency = getFrequency();
    if (workWithFunction())
        current_state.function = getFunction();
    if (workWithInverse())
        current_state.inverse = getInverse();
    if (workWithSynchronization())
        current_state.synchronization = getSynchronization();
    if (workWithOutputImpedance())
        current_state.outputImpedance = getOutputImpedance();
    if (workWithAMDepth())
        current_state.amDepth = getAMDepth();
    if (workWithFMSpan())
        current_state.fmSpan = getFMSpan();
    if (workWithModulationFunction())
        current_state.modulationFunction = getModulationFunction();
    if (workWithModulationEnabled())
        current_state.modulationEnabled = getModulationEnabled();
    if (workWithModulationType())
        current_state.modulationType = getModulationType();
    if (workWithModulationRate())
        current_state.modulationRate = getModulationRate();
    if (workWithModulationSpan())
        current_state.modulationSpan = getModulationSpan();

    return current_state;
}

///выставляет состояние генератора, принимает в переменных только структуру struct Generator_State
bool Generator::setState(const Generator_State &state)
{
    bool result = true;

    if (state.model != this->generatorModel)
        result = false;
    if (workWithAmplitude())
        result &= this->setAmplitude(state.amplitude, "VR");
    if (workWithOffset())
        result &= this->setOffset(state.offset);
    if (workWithFrequency())
        result &= this->setFrequency(state.frequency);
    if (workWithFunction())
        result &= this->setFunction(state.function);
    if (workWithInverse())
        result &= this->setInverse(state.inverse);
    if (workWithSynchronization())
        result &= this->setSynchronization(state.synchronization);
    if (workWithOutputImpedance())
        result &= this->setOutputImpedance(state.outputImpedance);
    if (workWithAMDepth())
        result &= this->setAMDepth(state.amDepth);
    if (workWithFMSpan())
        result &= this->setFMSpan(state.fmSpan);
    if (workWithModulationFunction())
        result &= this->setModulationFunction(state.modulationFunction);
    if (workWithModulationEnabled())
        result &= this->setModulationEnabled(state.modulationEnabled);
    if (workWithModulationType())
        result &= this->setModulationType(state.modulationType);
    if (workWithModulationRate())
        result &= this->setModulationRate(state.modulationRate);
    if (workWithModulationSpan())
        result &= this->setModulationSpan(state.modulationSpan);

    return result;
}

//void Generator::wait(const double &x) const
//{
//    QTest::qWait(_round(this->waitTime*x));

//    return;
//}

//void Generator::setDS335(DS335 *new_ds335)
//{
//    this->ds335 = new_ds335;
//    init();

//    return;
//}

//DS335* Generator::getDS335() const
//{
//    return this->ds335;
//}

//void Generator::setDS345(DS345 *new_ds345)
//{
//    this->ds345 = new_ds345;
//    init();

//    return;
//}

//DS345* Generator::getDS345() const
//{
//    return this->ds345;
//}

//bool Generator::openSerial(QSerialPort *serial) const
//{
//    return this->srs->openSerial(serial);
//}

///возвращает Вектор стрингов возможных моделей
std::vector<std::string> Generator::getSupportedModels() const
{
    std::vector<std::string> ans;

    ans.push_back("DS335");
    ans.push_back("DS345");

    ans.push_back("AUTO");

    return ans;
}

///выставляет модель
void Generator::setGeneratorModel(const std::string &new_generatorModel)
{
    this->generatorModel = new_generatorModel;

    return;
}

///возвращает модель
std::string Generator::getGeneratorModel() const
{
    return this->generatorModel;
}

//∂ пока не знаю, как это реализовать без Qt это
//bool Generator::autoSetGeneratorModel(QSerialPort *serial)
//{
//    this->generatorModel.clear();

//    QString model = this->srs->autoDetect(serial);

//    if (model.trimmed().isEmpty()) {
//        this->srs->disconnect(serial);

//        return false;
//    }

//    this->generatorModel = model;
//    if (model == "DS335") {
//        this->ds335 = new DS335();
//        this->ds335->setSerial(serial);
//        init();

//        return true;
//    }
//    if (model == "DS345") {
//        this->ds345 = new DS345();
//        this->ds345->setSerial(serial);
//        init();

//        return true;
//    }

//    this->srs->disconnect(serial);

//    return false;
//}

//∂ пока не знаю, как это реализовать без Qt это
//bool Generator::autoSetGeneratorModel(const QString &portName, const int &baudrate)
//{
//    QSerialPort *serial = new QSerialPort();

//    serial->setPortName(portName);
//    serial->setBaudRate(baudrate);
//    serial->setDataBits(QSerialPort::Data8);

//    serial->setParity(QSerialPort::NoParity);
//    serial->setStopBits(QSerialPort::OneStop);
//    if(autoSetGeneratorModel(serial))
//        return true;
//    serial->setParity(QSerialPort::OddParity);
//    serial->setStopBits(QSerialPort::OneStop);
//    if(autoSetGeneratorModel(serial))
//        return true;
//    serial->setParity(QSerialPort::EvenParity);
//    serial->setStopBits(QSerialPort::OneStop);
//    if(autoSetGeneratorModel(serial))
//        return true;
//    serial->setParity(QSerialPort::NoParity);
//    serial->setStopBits(QSerialPort::TwoStop);
//    if(autoSetGeneratorModel(serial))
//        return true;
//    serial->setParity(QSerialPort::OddParity);
//    serial->setStopBits(QSerialPort::TwoStop);
//    if(autoSetGeneratorModel(serial))
//        return true;
//    serial->setParity(QSerialPort::EvenParity);
//    serial->setStopBits(QSerialPort::TwoStop);
//    if(autoSetGeneratorModel(serial))
//        return true;

//    return autoSetGeneratorModel(serial);
//}

//∂ пока не знаю, как это реализовать без Qt это
//bool Generator::autoSetGeneratorModel(const QString &portName)
//{
//    QStringList baudrates = this->srs->getBaudrateList();
//    for (int baud = 0;baud < baudrates.size();baud++) {
//        int baudrate = baudrates[baud].toInt();

//        if (autoSetGeneratorModel(portName, baudrate))
//            return true;
//    }

//    return false;
//}

// вместо этих 2 использую 4 (SET)connect'a
//bool Generator::setConnection(const QString &portName, const int &baudrate, const int &stopBit, const int &parity, const QString &new_generatorModel)
//{
//	QString _generatorModel = new_generatorModel.trimmed().toUpper();
//    if (_generatorModel == "DS335") {
//        if (this->ds335 == nullptr)
//            this->ds335 = new DS335();
//        this->generatorModel = "DS335";
//        init();

//        return this->ds335->setConnection(portName, baudrate, stopBit, parity);
//    }
//    if (_generatorModel == "DS345") {
//        if (this->ds345 == nullptr)
//            this->ds345 = new DS345();
//        this->generatorModel = "DS345";
//        init();

//        return this->ds345->setConnection(portName, baudrate, stopBit, parity);
//    }
//    if (_generatorModel.isEmpty() ||
//        _generatorModel == "AUTO") {
//        QSerialPort *serial = new QSerialPort();
//        serial->setPortName(portName);
//        serial->setBaudRate(baudrate);

//        if (stopBit == 1)
//            serial->setStopBits(QSerialPort::OneStop);
//        if (stopBit == 2)
//            serial->setStopBits(QSerialPort::TwoStop);
//        if (stopBit == 3)
//            serial->setStopBits(QSerialPort::OneAndHalfStop);

//        if (parity == 0)
//            serial->setParity(QSerialPort::NoParity);
//        if (parity == 1)
//            serial->setParity(QSerialPort::OddParity);
//        if (parity == 2)
//            serial->setParity(QSerialPort::EvenParity);
        
//        return autoSetGeneratorModel(serial);
//    }

//    return false;
//}

//bool Generator::setConnectionBrute(const QString &portName, const QString &new_generatorModel)
//{
//    QStringList baudRates = this->srs->getBaudrateList();
//    for (int i = 0;i < baudRates.length();i++) {
//        if (setConnection(portName, baudRates[i].toInt(), 1, 0, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 1, 1, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 1, 2, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 0, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 1, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 2, new_generatorModel))
//            return true;
//    }

//    return false;
//}

///№1 устанавливает соединение, принимает (new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control, _generatorModel)
bool Generator::SETconnect(const std::string &new_port_name, const std::string &new_baudrate, const std::string &new_data_bits, const std::string &new_stop_bits, const std::string &new_parity, const std::string &new_flow_control, const std::string &_generatorModel) {
    //setGeneratorModel(_generatorModel); // от Вити. Считай, что new_generatorModel===_generatorModel
    //∂ а вообще чем эти ToUpper обусловлены, на всякий случай что ли?
    //	QString _generatorModel = new_generatorModel.trimmed().toUpper();
        if (_generatorModel == "DS335") {
            if (this->ds335 == nullptr)
                this->ds335 = new DS335();
            this->generatorModel = "DS335";
            init();

            return this->ds335->connect(new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control);//(portName, baudrate, dataBit, stopBit, parity, flowcontrol, );//setConnection(portName, baudrate, stopBit, parity);
        }
        if (_generatorModel == "DS345") {
            if (this->ds345 == nullptr)
                this->ds345 = new DS345();
            this->generatorModel = "DS345";
            init();

            return this->ds345->connect(new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control); //setConnection(portName, baudrate, stopBit, parity);
        }
    return false;
}

//bool Generator::setConnectionBrute(const QString &portName, const QString &new_generatorModel)
//{
//    QStringList baudRates = this->srs->getBaudrateList();
//    for (int i = 0;i < baudRates.length();i++) {
//        if (setConnection(portName, baudRates[i].toInt(), 1, 0, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 1, 1, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 1, 2, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 0, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 1, new_generatorModel))
//            return true;
//        if (setConnection(portName, baudRates[i].toInt(), 2, 2, new_generatorModel))
//            return true;
//    }
//}

///№2 устанавливает соединение, принимает (new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control). _generatorModel запрашивает и определяет сам
bool Generator::SETconnect(const std::string &new_port_name, const std::string &new_baudrate, const std::string &new_data_bits, const std::string &new_stop_bits, const std::string &new_parity, const std::string &new_flow_control) {
    //∂ а вообще чем эти ToUpper обусловлены, на всякий случай чnоли?
    //	QString _generatorModel = new_generatorModel.trimmed().toUpper();
        if (this->generatorModel == "DS335") { // this->getGeneratorModel() (_generatorModel == "DS335")
            if (this->ds335 == nullptr)
                this->ds335 = new DS335();
            init();

            return this->ds335->connect(new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control);//(portName, baudrate, dataBit, stopBit, parity, flowcontrol, );//setConnection(portName, baudrate, stopBit, parity);
        }
        if (this->generatorModel == "DS345") {
            if (this->ds345 == nullptr)
                this->ds345 = new DS345();
            init();

            return this->ds345->connect(new_port_name, new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control); //setConnection(portName, baudrate, stopBit, parity);
        }
    return false;
}

///№3 устанавливает соединение, принимает (new_port_name, new_baudrate). new_data_bits, new_stop_bits, new_parity, new_flow_control и_generatorModel запрашивает и определяет сам
bool Generator::SETconnect(const std::string &new_port_name, const std::string &new_baudrate) {
    if (this->generatorModel == "DS335") { // this->getGeneratorModel() (_generatorModel == "DS335")
        if (this->ds335 == nullptr)
            this->ds335 = new DS335();
        init();

        return this->ds335->connect(new_port_name, new_baudrate);
    }
    if (this->generatorModel == "DS345") {
        if (this->ds345 == nullptr)
            this->ds345 = new DS345();
        init();

        return this->ds345->connect(new_port_name, new_baudrate);
    }
    return false;
}

///№4 устанавливает соединение, принимает (new_port_name). new_baudrate, new_data_bits, new_stop_bits, new_parity, new_flow_control и_generatorModel запрашивает и определяет сам
bool Generator::SETconnect(const std::string &new_port_name) {
    if (this->generatorModel == "DS335") { // this->getGeneratorModel() (_generatorModel == "DS335")
        if (this->ds335 == nullptr)
            this->ds335 = new DS335();
        init();

        return this->ds335->connect(new_port_name);
    }
    if (this->generatorModel == "DS345") {
        if (this->ds345 == nullptr)
            this->ds345 = new DS345();
        init();

        return this->ds345->connect(new_port_name);
    }
    return false;
}

///обрывает соединение
bool Generator::disconnect() const
{
    if (this->generatorModel == "DS335") {
        this->ds335->disconnect();

        return true;
    }
    if (this->generatorModel == "DS345") {
        this->ds345->disconnect();

        return true;
    }

    return false;
}

///возвращает Вектор стрингов возможных Baudrate
std::vector<std::string> Generator::getBaudrateList() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getBaudrateList();
    if (this->generatorModel == "DS345")
        return this->ds345->getBaudrateList();
    else return {"Empty BaudrateList"};
}

///проверяет, что для обоих моделей Baudrate верен и возможен
bool Generator::isValidBaudrateAll(const int &baudrate) const
{
    DS335 temp335;
    DS345 temp345;
    bool answer = temp335.isValidBaudrate(baudrate);
    answer &= temp345.isValidBaudrate(baudrate);
    return answer;
}

///проверяет, что для модели выставлен верный Baudrate
bool Generator::isValidBaudrate(const int &baudrate) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isValidBaudrate(baudrate);
    if (this->generatorModel == "DS345")
        return this->ds345->isValidBaudrate(baudrate);
    return false;
}

//∂ пока лень разбираться, мб обойдемся
//bool Generator::changeBaudrate(const int &baudrate)
//{
//    if (this->generatorModel == "DS335")
//        return this->ds335->setBaudRate(baudrate);
//    if (this->generatorModel == "DS345")
//        return this->ds345->changeBaudrate(baudrate);
//    return false;
//}

///∂выставляет время для записи
void Generator::setWriteTimeout(const int &new_writeTimeout)
{
    if (this->generatorModel == "DS335")
        return this->ds335->setWriteTimeout(new_writeTimeout);
    if (this->generatorModel == "DS345")
        return this->ds345->setWriteTimeout(new_writeTimeout);
    return;
}

///возвращает время для записи
int Generator::getWriteTimeout() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getWriteTimeout();
    if (this->generatorModel == "DS345")
        return this->ds345->getWriteTimeout();
    return 0;
}

///∂выставляет время для чтения
void Generator::setReadTimeout(const int &new_readTimeout)
{
    if (this->generatorModel == "DS335")
        return this->ds335->setReadTimeout(new_readTimeout);
    if (this->generatorModel == "DS345")
        return this->ds345->setReadTimeout(new_readTimeout);
    return;
}

///возвращает время для чтения
int Generator::getReadTimeout() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getReadTimeout();
    if (this->generatorModel == "DS345")
        return this->ds345->getReadTimeout();
    return 0;
}

///∂выставляет время для ожидания
void Generator::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    if (this->generatorModel == "DS335")
        return this->ds335->setReadWaitTimeout(new_readWaitTimeout);
    if (this->generatorModel == "DS345")
        return this->ds345->setReadWaitTimeout(new_readWaitTimeout);
    return;
}

///возвращает время для чтения
int Generator::getReadWaitTimeout() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getReadWaitTimeout();
    if (this->generatorModel == "DS345")
        return this->ds345->getReadWaitTimeout();
    return 0;
}

//∂ см в DS335.h
//void Generator::setAttemptsToConnect(const int &new_attemptsToConnect)
//{
//    if (this->generatorModel == "DS335")
//        return this->ds335->setAttemptsToConnect(new_attemptsToConnect);
//    if (this->generatorModel == "DS345")
//        return this->ds345->setAttemptsToConnect(new_attemptsToConnect);
//    return;
//}

//int Generator::getAttemptsToConnect() const
//{
//    if (this->generatorModel == "DS335")
//        return this->ds335->getAttemptsToConnect();
//    if (this->generatorModel == "DS345")
//        return this->ds345->getAttemptsToConnect();
//    return 0;
//}

///∂проверяет, что генератор живой
bool Generator::isActive() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isActive();
    if (this->generatorModel == "DS345")
        return this->ds345->isActive();
    return false;
}

///стандартная ф-ция отправки команды
bool Generator::send(const std::string &command, std::string &response, const bool &wait_for_response) const //(const QString &command, QString &response, const bool &wait_for_response) const //, const std::string &terminate // terminate я на самом деле опционально добавил - исходно его не было. А для всего SRS по умолчанию  он везде и всегда \n

{
    if (this->generatorModel == "DS335")
        return this->ds335->send(command, response, wait_for_response);
    if (this->generatorModel == "DS345")
        return this->ds345->send(command, response, wait_for_response);
    return false;
}

///ф-ция отправки команды в случае, если НЕ ждём ответа
bool Generator::sendCommand(const std::string &command) const //, const std::string &terminate
{
    if (this->generatorModel == "DS335")
        return this->ds335->sendCommand(command);
    if (this->generatorModel == "DS345")
        return this->ds345->sendCommand(command);
    return false;
}

///ф-ция отправки команды в случае, если ждём ответа
bool Generator::sendQuery(const std::string &command, std::string &response) const //, const std::string &terminate
{
    if (this->generatorModel == "DS335")
        return this->ds335->sendQuery(command, response);
    if (this->generatorModel == "DS345")
        return this->ds345->sendQuery(command, response);
    return false;
}

///ф-ция отправки команды в случае, если ждём ответа. По сути, урезанный sendQuery, он сам выставляет значения "лишних" переменных и сам создает str для записи responce
std::string Generator::ask(const std::string &command) const //, const std::string &terminate
{
    if (this->generatorModel == "DS335")
        return this->ds335->ask(command);
    if (this->generatorModel == "DS345")
        return this->ds345->ask(command);
    return "";
}

///возвращает IDN
std::string Generator::getIDN(bool* succeed) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getIDN(succeed);
    if (this->generatorModel == "DS345")
        return this->ds345->getIDN(succeed);
    return "empty IDN";
}

///устанавливает настройки по умолчанию
bool Generator::setDefaultSettings() const
{
    bool ans = true;



    if (workWithFunction())
        ans &= setDefaultFunction();
    if (workWithAmplitude())
        ans &= setDefaultAmplitude();
    if (workWithOffset())
        ans &= setDefaultOffset();
    if (workWithFrequency())
        ans &= setDefaultFrequency();
    if (workWithInverse())
        ans &= setDefaultInverse();
    if (workWithSynchronization())//workWithSynchronization() only 335
        ans &= setDefaultSynchronization();
    if (workWithOutputImpedance())//workWithImpedance() only 335
        ans &= setDefaultOutputImpedance();
    if (workWithAMDepth())
        ans &= setDefaultAMDepth();
    if (workWithFMSpan())
        ans &= setDefaultFMSpan();
    if (workWithModulationFunction())
        ans &= setDefaultModulationFunction();
    if (workWithModulationEnabled())
        ans &= setDefaultModulationEnabled();
    if (workWithModulationType())
        ans &= setDefaultModulationType();
    if (workWithModulationRate())
        ans &= setDefaultModulationRate();
    if (workWithModulationSpan())
        ans &= setDefaultModulationSpan();

    return ans;
}

// ///∂ пока не знаю, зачем пригодится, но оставлю
//double Generator::getAverageInputTime() const
//{
//    if (this->generatorModel == "DS335")
//        return 1;
//    if (this->generatorModel == "DS345")
//        return 1;
//    return 1E5;
//}

// ///∂ пока не знаю, зачем пригодится, но оставлю
//double Generator::getAverageOutputTime() const
//{
//    if (this->generatorModel == "DS335")
//        return 30;
//    if (this->generatorModel == "DS345")
//        return 30;
//    return 1E5;
//}

///проверяет возможность работы с амплитудой
bool Generator::workWithAmplitude() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает амплитуду по умолчанию
double Generator::getDefaultAmplitude() const
{
    if (this->generatorModel == "DS335")
        return 1;
    if (this->generatorModel == "DS345")
        return 1;
    return -1;
}

///устанавливает амплитуду по умолчанию
bool Generator::setDefaultAmplitude() const
{
    return setAmplitude(getDefaultAmplitude(), "VR");
}

///возвращает Вектор возможных типов значений напряжения для амплитуды
std::vector<std::string> Generator::getAmplitudeTypeList() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getAmplitudeTypeList();
    if (this->generatorModel == "DS345")
        return this->ds345->getAmplitudeTypeList();
    else return {"Empty AmplitudeTypeList"};
}

//УЖЕ РЕАЛИЗОВАНО:  по хорошему тут и дальше  во всех геттерах бы реализовать проверку, что тип unit присылается правильный
/// возвращает минимальную амплитуду
double Generator::getMinAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinAmplitude(waveform, outputZ, unit);
    if (this->generatorModel == "DS345") {
        return this->ds345->getMinAmplitude(waveform, unit);
    }
    return -1;
}

//∂ почему _Default_ OutputImpedance?
/// возвращает минимальную амплитуду из запроса в каких величинах её выдать и какая сейчас Function==waveform. Сам определяет, какой сейчас DefaultOutputImpedance
double Generator::getMinAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinAmplitude(waveform, getDefaultOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getMinAmplitude(waveform, unit);
    return -1;
}


/// возвращает минимальную амплитуду чисто из запроса в каких величинах её выдать. Сам определяет, какая сейчас Function==waveform и какой OutputImpedance
double Generator::getMinAmplitudeCurrent(const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinAmplitude(getFunction(), getOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getMinAmplitude(getFunction(), unit);
    return -1;
}

/// возвращает максимальную амплитуду
double Generator::getMaxAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxAmplitude(waveform, outputZ, unit);
    if (this->generatorModel == "DS345") {
        return this->ds345->getMaxAmplitude(waveform, unit);
    }
    return -1;
}

//∂ почему _Default_ OutputImpedance?
/// возвращает максимальную амплитуду из запроса в каких величинах её выдать и какая сейчас Function==waveform. Сам определяет, какой сейчас DefaultOutputImpedance
double Generator::getMaxAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxAmplitude(waveform, getDefaultOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxAmplitude(waveform, unit);
    return -1;
}

/// возвращает максимальную амплитуду чисто из запроса в каких величинах её выдать. Сам определяет, какая сейчас Function==waveform и какой OutputImpedance
double Generator::getMaxAmplitudeCurrent(const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxAmplitude(getFunction(), getOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxAmplitude(getFunction(), unit);
    return -1;
}

/// возвращает шаг амплитуды
double Generator::getStepAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepAmplitude(waveform, outputZ, unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getStepAmplitude(waveform, unit);
    return -1;
}

//∂ почему _Default_ OutputImpedance?
/// возвращает шаг амплитуды из запроса в каких величинах её выдать и какая сейчас Function==waveform. Сам определяет, какой сейчас DefaultOutputImpedance
double Generator::getStepAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepAmplitude(waveform, getDefaultOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getStepAmplitude(waveform, unit);
    return -1;
}

/// возвращает шаг амплитуды чисто из запроса в каких величинах её выдать. Сам определяет, какая сейчас Function==waveform и какой OutputImpedance
double Generator::getStepAmplitudeCurrent(const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepAmplitude(getFunction(), getOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getStepAmplitude(getFunction(), unit);
    return -1;
}

///∂ серьезно, что это такое??
double Generator::getDecimalsAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsAmplitude(waveform, outputZ, unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsAmplitude(waveform, unit);
    return -1;
}

//∂ почему _Default_ OutputImpedance?
///∂ серьезно, что это такое??
double Generator::getDecimalsAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsAmplitude(waveform, getDefaultOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsAmplitude(waveform, unit);
    return -1;
}

///∂ серьезно, что это такое??
double Generator::getDecimalsAmplitudeCurrent(const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsAmplitude(getFunction(), getOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsAmplitude(getFunction(), unit);
    return -1;
}

///проверяет, что аплитуда для заданной формы сигнала не выходит за допустимые границы
bool Generator::isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isValidAmplitude(amplitude, waveform, outputZ, unit);
    if (this->generatorModel == "DS345")
        return this->ds345->isValidAmplitude(amplitude, waveform, unit);
    return false;
}

//∂ почему _Default_ OutputImpedance?
///проверяет, что аплитуда для заданной формы сигнала не выходит за допустимые границы, при этом сама определяет DefaultOutputImpedance
bool Generator::isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isValidAmplitude(amplitude, waveform, getDefaultOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->isValidAmplitude(amplitude, waveform, unit);
    return false;
}

/// проверяет, что аплитуда для заданной формы сигнала не выходит за допустимые границы, при этом сам определяет, какая сейчас Function==waveform и OutputImpedance
/// \brief Собственная разработка для проверки на адекватную величину (внутри допустимого диапазона) для функции setAmplitude
bool Generator::isValidAmplitude(const double &amplitude, const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isValidAmplitude(amplitude, getFunction(), getOutputImpedance(), unit);
    if (this->generatorModel == "DS345")
        return this->ds345->isValidAmplitude(amplitude, getFunction(), unit);
    return false;
}

/// проверяет, что отправлена правильная единица измерения амплитуды сигнала
bool Generator::isValidAmplitudeType(const std::string &unit) const
{
    if (this->generatorModel == "DS335") {
        return this->ds335->isValidAmplitudeType(unit);
    }
    if (this->generatorModel == "DS345")
        return this->ds345->isValidAmplitudeType(unit);
    return false;
}

///устанавливает амплитуду
bool Generator::setAmplitude(const double &amplitude, const std::string &unit) const
{
    if (!isValidAmplitude(amplitude, unit)) //Собственная разработка для проверки на адекватную величину (внутри допустимого диапазона)
        return false;
    if (this->generatorModel == "DS335") {
        return this->ds335->setAmplitude(amplitude, unit); // оба типа данных можно устанавливать и считывать:Abridged Command List ix, не знаю почему Гоша посчитал что считывать можно только VR
    }
    if (this->generatorModel == "DS345")
        return this->ds345->setAmplitude(amplitude, unit);
    return false;
}

///возвращает амплитуду
double Generator::getAmplitude(const std::string &unit) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getAmplitude(unit);
    if (this->generatorModel == "DS345")
        return this->ds345->getAmplitude(unit);
    return -1;
}

///проверяет возможность работы со смещением
bool Generator::workWithOffset() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращают смещение по умолчанию
double Generator::getDefaultOffset() const
{
    if (this->generatorModel == "DS335")
        return 0;
    if (this->generatorModel == "DS345")
        return 0;
    return -1;
}

///устанавливает смещение по умолчанию
bool Generator::setDefaultOffset() const
{
    return setOffset(getDefaultOffset());
}

///возвращает минимальное смещение
double Generator::getMinOffset() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinOffset();
    if (this->generatorModel == "DS345")
        return this->ds345->getMinOffset();
    return -1;
}

///возвращает максимальное смещение
double Generator::getMaxOffset() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxOffset();
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxOffset();
    return -1;
}

///возвращает шаг смещения
double Generator::getStepOffset() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepOffset();
    if (this->generatorModel == "DS345")
        return this->ds345->getStepOffset();
    return -1;
}

///∂ что это такое?
double Generator::getDecimalsOffset() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsOffset();
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsOffset();
    return -1;
}

///проверяет что установлено адекватное смещение (т.е. внутри допустимого диапазона)
bool Generator::isValidOffset(const double &offset) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->isValidOffset(offset);
    if (this->generatorModel == "DS345")
        return this->ds345->isValidOffset(offset);
    return false;
}

///устанавливает смещение
bool Generator::setOffset(const double &offset) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setOffset(offset);
    if (this->generatorModel == "DS345")
        return this->ds345->setOffset(offset);
    return false;
}

///возвращает смещение
double Generator::getOffset() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getOffset();
    if (this->generatorModel == "DS345")
        return this->ds345->getOffset();
    return -1;

}

///проверяет возможность работы с частотой
bool Generator::workWithFrequency() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает частоту по умолчанию
double Generator::getDefaultFrequency() const
{
    if (this->generatorModel == "DS335")
//        return this->ds335->getMinFrequency(getDefaultFunction());
        return 1E4;
    if (this->generatorModel == "DS345")
//        return this->ds345->getMinFrequency(getDefaultFunction());
        return 1E4;
    return -1;
}

///устанавливает частоту по умолчанию
bool Generator::setDefaultFrequency() const
{
    return setFrequency(getDefaultFrequency());
}

///возвращает минимальную чистоту
double Generator::getMinFrequency(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinFrequency(waveform);
    if (this->generatorModel == "DS345")
        return this->ds345->getMinFrequency(waveform);
    return -1;
}

///возвращает минимальную чистоту. Сам определяет, какая сейчас Function==waveform
double Generator::getMinFrequencyCurrent() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMinFrequency(getFunction());
    if (this->generatorModel == "DS345")
        return this->ds345->getMinFrequency(getFunction());
    return -1;
}

///возвращает максимальную частоту
double Generator::getMaxFrequency(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxFrequency(waveform);
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxFrequency(waveform);
    return -1;
}

///возвращает максимальную чистоту. Сам определяет, какая сейчас Function==waveform
double Generator::getMaxFrequencyCurrent() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getMaxFrequency(getFunction());
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxFrequency(getFunction());
    return -1;
}

///возвращает шаг частоты
double Generator::getStepFrequency(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepFrequency(waveform);
    if (this->generatorModel == "DS345")
        return this->ds345->getStepFrequency(waveform);
    return -1;
}

///возвращает шаг частоты. Сам определяет, какая сейчас Function==waveform
double Generator::getStepFrequencyCurrent() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getStepFrequency(getFunction());
    if (this->generatorModel == "DS345")
        return this->ds345->getStepFrequency(getFunction());
    return -1;
}

///∂ что это такое?
double Generator::getDecimalsFrequency(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsFrequency(waveform);
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsFrequency(waveform);
    return -1;

}

///∂ что это такое?
double Generator::getDecimalsFrequencyCurrent() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getDecimalsFrequency(getFunction());
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsFrequency(getFunction());
    return -1;
}

/////проверяет, что частота для заданной формы сигнала не выходит за допустимые границы
//bool Generator::isValidFrequency(const double &frequency, const std::string &waveform) const
//{
//    std::string current_waveform = waveform;
//    if (waveform == "")// проверка на пустоту
//        current_waveform = getFunction();
//    return (frequency >= getMinFrequency(current_waveform) &&
//            frequency <= getMaxFrequency(current_waveform));
//}

/// проверяет, что частота для заданной формы сигнала не выходит за допустимые границы, при этом сам определяет, какая сейчас Function==waveform
/// \brief Собственная разработка для проверки на адекватную величину (внутри допустимого диапазона) для функции setFrequency
bool Generator::isValidFrequency(const double &frequency) const
{
    return (frequency >= getMinFrequency(getFunction()) &&
            frequency <= getMaxFrequency(getFunction()));
}

///устанавливает частоту
bool Generator::setFrequency(const double &frequency) const
{
    if(!isValidFrequency(frequency)) //
        return false;
    if (this->generatorModel == "DS335")
        return this->ds335->setFrequency(frequency);
    if (this->generatorModel == "DS345")
        return this->ds345->setFrequency(frequency);
    return false;
}

///возвращает частоту
double Generator::getFrequency() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getFrequency();
    if (this->generatorModel == "DS345")
        return this->ds345->getFrequency();
    return -1;
}

/// проверяет возможность работы с типом функции Function==waveform
bool Generator::workWithFunction() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает функцию по умолчанию
std::string Generator::getDefaultFunction() const
{
    if (this->generatorModel == "DS335")
        return "SINE";
    if (this->generatorModel == "DS345")
        return "SINE";
    return "";
}

///устанавливает функцию по умолчанию
bool Generator::setDefaultFunction() const
{
    return setFunction(getDefaultFunction());
}

///возвращает Вектор возможных функций
std::vector<std::string> Generator::getFunctionList() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getFunctionList();
    if (this->generatorModel == "DS345")
        return this->ds345->getFunctionList();
    return {"FunctionList is Empty"};
}

///Сопоставляет строчку с её номером и выдаёт последний
int Generator::functionNumberFromString(const std::string &function_string) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->functionNumberFromString(function_string);
    if (this->generatorModel == "DS345")
        return this->ds345->functionNumberFromString(function_string);
    return -1;
}

///Сопоставляет номер строчки с самойстрочкой и выдаёт последнюю
std::string Generator::functionStringFromNumber(const int &function_number) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->functionStringFromNumber(function_number);
    if (this->generatorModel == "DS345")
        return this->ds345->functionStringFromNumber(function_number);
    return "";
}

///устанавливает функцию по её номеру
bool Generator::setFunction(const int &function) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setFunction(function);
    if (this->generatorModel == "DS345")
        return this->ds345->setFunction(function);
    return false;
}

///устанавливает функцию по её названию
bool Generator::setFunction(const std::string &function) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setFunction(function);
    if (this->generatorModel == "DS345")
        return this->ds345->setFunction(function);
    return false;
}

///возвращает название функции
std::string Generator::getFunction() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getFunction();
    if (this->generatorModel == "DS345")
        return this->ds345->getFunction();
    return "";
}

///проверяет возможность работы с инверсией
bool Generator::workWithInverse() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает инверсию по умолчанию
bool Generator::getDefaultInverse() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///устанавливает инверсию по умолчанию
bool Generator::setDefaultInverse() const
{
    return setInverse(getDefaultInverse());
}

///устанавливает инверсия
bool Generator::setInverse(const bool &inverse) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setInverse(inverse);
    if (this->generatorModel == "DS345")
        return this->ds345->setInverse(inverse);
    return false;
}

///возвращает инверсия
bool Generator::getInverse() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getInverse();
    if (this->generatorModel == "DS345")
        return this->ds345->getInverse();
    return false;
}

///проверяет возможность работы с синхронизацией
bool Generator::workWithSynchronization() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///возвращает синхронизацию по умолчанию
bool Generator::getDefaultSynchronization() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///устанавливает синхронизацию по умолчанию
bool Generator::setDefaultSynchronization() const
{
    return setSynchronization(getDefaultSynchronization());
}

///устанавливает синхронизацию
bool Generator::setSynchronization(const bool &synchronization) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setSynchronization(synchronization);
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///возвращает синхронизацию
bool Generator::getSynchronization() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getSynchronization();
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///проверяет возможность работы с выходным импедансом
bool Generator::workWithOutputImpedance() const
{
    if (this->generatorModel == "DS335")
        return true;
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///возвращает выходной импеданс по умолчанию
std::string Generator::getDefaultOutputImpedance() const
{
    if (this->generatorModel == "DS335")
        return "Hi-Z";
    if (this->generatorModel == "DS345")
        return "";
    return "";
}

///устанавливает выходной импеданс по умолчанию
bool Generator::setDefaultOutputImpedance() const
{
    return setOutputImpedance(getDefaultOutputImpedance());
}

///возвращает вектор выходных импедансов
std::vector<std::string> Generator::getOutputImpedanceList() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getOutputImpedanceList();
    if (this->generatorModel == "DS345")
        return {"Empty OutputImpedanceList"};
    return {"Empty OutputImpedanceList"};
}

///Сопоставляет строчку импеданса с её номером и выдаёт последний
int Generator::outputImpedanceNumberFromString(const std::string &outputImpedance_string) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->outputImpedanceNumberFromString(outputImpedance_string);
    if (this->generatorModel == "DS345")
        return -1;
    return -1;
}

///Сопоставляет номер строчки импеданса с самойстрочкой импеданса и выдаёт последнюю
std::string Generator::outputImpedanceStringFromNumber(const int &outputImpedance_number) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->outputImpedanceStringFromNumber(outputImpedance_number);
    if (this->generatorModel == "DS345")
        return "";
    return "";
}

///устанавливает выходной импеданс через его номер
bool Generator::setOutputImpedance(const int &outputImpedance) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setOutputImpedance(outputImpedance);
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///устанавливает выходной импеданс через его название
bool Generator::setOutputImpedance(const std::string &outputImpedance) const
{
    if (this->generatorModel == "DS335")
        return this->ds335->setOutputImpedance(outputImpedance);
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///возвращает выходной импеданс через его название
std::string Generator::getOutputImpedance() const
{
    if (this->generatorModel == "DS335")
        return this->ds335->getOutputImpedance();
    if (this->generatorModel == "DS345")
        return "";
    return "";
}

///проверяет возможность работы с амплитудной модуляцией
bool Generator::workWithAMDepth() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает глубину амплитудной модуляции по умолчанию
int Generator::getDefaultAMDepth() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return 0;
    return -1;
}

///устанавливает глубину амплитудной модуляции по умолчанию
bool Generator::setDefaultAMDepth() const
{
    return setAMDepth(getDefaultAMDepth());
}

///возвращает минимальную глубину амплитудной модуляции
int Generator::getMinAMDepth() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinAMDepth();
    return -1;
}

///возвращает максимальную глубину амплитудной модуляции
int Generator::getMaxAMDepth() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxAMDepth();
    return -1;
}

///проверяет, что глубина амплитудной модуляции не выходит за допустимые границы
bool Generator::isValidAMDepth(const int &persentage) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidAMDepth(persentage);
    return false;
}

///устанавливает глубину амплитудной модуляции
bool Generator::setAMDepth(const int &persentage) const
{
    if (!isValidAMDepth(persentage)) //
        return false;
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setAMdepth(persentage);
    return false;
}

///возвращает глубину амплитудной модуляции
int Generator::getAMDepth() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getAMdepth();
    return -1;
}

///проверяет возможность работы с частотной модуляцией
bool Generator::workWithFMSpan() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

/// возвращает интервал==Span частотной модуляции по умолчанию
double Generator::getDefaultFMSpan() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinFMSpan(getDefaultFunction());
    return -1;
}

///устанавливает интервал частотной модуляции по умолчанию
bool Generator::setDefaultFMSpan() const
{
    return setFMSpan(getDefaultFMSpan());
}

///возвращает минимальный интервал частотной модуляции
double Generator::getMinFMSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinFMSpan(waveform);
    return -1;
}

///возвращает минимальный интервал частотной модуляции. Сам определяет, какая сейчас Function==waveform
double Generator::getMinFMSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinFMSpan(getFunction());
    return -1;
}

///возвращает максимальный интервал частотной модуляции
double Generator::getMaxFMSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxFMSpan(waveform);
    return -1;
}

///возвращает максимальный интервал частотной модуляции. Сам определяет, какая сейчас Function==waveform
double Generator::getMaxFMSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxFMSpan(getFunction());
    return -1;
}

///проверяет, что интервал для заданной формы сигнала не выходит за допустимые границы
bool Generator::isValidFMSpan(const int &span, const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidFMSpan(span, waveform);
    return false;
}

///проверяет, что интервал для заданной формы сигнала не выходит за допустимые границы, при этом сам определяет, какая сейчас Function==waveform
/// \brief Собственная разработка для проверки на адекватную величину (внутри допустимого диапазона) для функции setFMSpan
bool Generator::isValidFMSpan(const int &span) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidFMSpan(span, getFunction());
    return false;
}

///устанавливает интервал частотной модуляции
bool Generator::setFMSpan(const double &span) const
{
    if (!isValidFMSpan(span)) //
        return false;
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setFMSpan(span);
    return false;
}

///возвращает интервал частотной модуляции
double Generator::getFMSpan() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getFMSpan();
    return -1;
}

///проверяет возможность работы с функцией модуляции (правый столбик в SWEEP/MODULATE)
bool Generator::workWithModulationFunction() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает функцию модуляции по умолчанию
std::string Generator::getDefaultModulationFunction() const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return "SINE";
    return "";
}

///устанавливает функцию модуляции по умолчанию
bool Generator::setDefaultModulationFunction() const
{
    return setModulationFunction(getDefaultModulationFunction());
}

///возвращает Вектор возможных функций модуляции
std::vector<std::string> Generator::getModulationFunctionList() const
{
    if (this->generatorModel == "DS335")
        return {"Empty ModulationFunctionList"};
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationFunctionList();
    return {"Empty ModulationFunctionList"};
}

///Сопоставляет строчку функции модуляции с её номером и выдаёт последний
int Generator::modulationFunctionNumberFromString(const std::string &function_string) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->modulationFunctionNumberFromString(function_string);
    return -1;
}

///Сопоставляет номер строчки функции модуляции с самой строчкой и выдаёт последнюю
std::string Generator::modulationFunctionStringFromNumber(const int &function_number) const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return this->ds345->modulationFunctionStringFromNumber(function_number);
    return "";
}

///устанавливает функцию модуляции через её номер
bool Generator::setModulationFunction(const int &function) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationFunction(function);
    return false;
}

///устанавливает функцию модуляции через её название
bool Generator::setModulationFunction(const std::string &function) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationFunction(function);
    return false;
}

///возвращает функцию модуляции через её название
std::string Generator::getModulationFunction() const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationFunction();
    return "";
}

///проверяет возможность работы с "включателем" модуляции
/// \brief см. DS345: Programming Commands 3-5 (стр. 55)
bool Generator::workWithModulationEnabled() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает положение "включателя" модуляции по умолчанию
bool Generator::getDefaultModulationEnabled() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return false;
    return false;
}

///устанавливает положение "включателя" модуляции по умолчанию
bool Generator::setDefaultModulationEnabled() const
{
    return setModulationEnabled(getDefaultModulationEnabled());
}

///переключает включатель модуляции
bool Generator::setModulationEnabled(const bool &enable) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationEnabled(enable);
    return false;
}

///возвращает положение включателя модуляции
bool Generator::getModulationEnabled() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationEnabled();
    return false;
}

///проверяет возможность работы с типом модуляции (левый столбик в SWEEP/MODULATE)
bool Generator::workWithModulationType() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает тип модуляции по умолчанию
std::string Generator::getDefaultModulationType() const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return "INTERNAL AM";
    return "";
}

///устанавливает тип модуляции по умолчанию
bool Generator::setDefaultModulationType() const
{
    return setModulationType(getDefaultModulationType());
}

///возвращает Вектор возможной модуляции
std::vector<std::string> Generator::getModulationTypeList() const
{
    if (this->generatorModel == "DS335")
       return {"Empty ModulationTypeList"};
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationTypeList();
    return {"Empty ModulationTypeList"};
}

///Сопоставляет строчку типа модуляции с её номером и выдаёт последний
int Generator::modulationTypeNumberFromString(const std::string &type_string) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->modulationTypeNumberFromString(type_string);
    return -1;
}

///Сопоставляет номер строчки типа модуляции с самой строчкой и выдаёт последнюю
std::string Generator::modulationTypeStringFromNumber(const int &type_number) const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return this->ds345->modulationTypeStringFromNumber(type_number);
    return "";
}

///устанавливает тип модуляции через его номер
bool Generator::setModulationType(const int &type) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationType(type);
    return false;
}

///устанавливает тип модуляции через его название
bool Generator::setModulationType(const std::string &type) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationType(type);
    return false;
}

///возвращает тип модуляции
std::string Generator::getModulationType() const
{
    if (this->generatorModel == "DS335")
        return "";
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationType();
    return "";
}

///проверяет возможность работы со скоростью==Rate модуляции
bool Generator::workWithModulationRate() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает скорость модуляции по умолчанию
double Generator::getDefaultModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinModulationRate();
    return -1;
}

///устанавливает скорость модуляции по умолчанию
bool Generator::setDefaultModulationRate() const
{
    return setModulationRate(getDefaultModulationRate());
}

///возвращает минимальную скорость модуляции
double Generator::getMinModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinModulationRate();
    return -1;
}

///возвращает максимальную скорость модуляции
double Generator::getMaxModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxModulationRate();
    return -1;
}

///возвращает шаг скорости модуляции
double Generator::getStepModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getStepModulationRate();
    return -1;
}

///∂ что это такое?
double Generator::getDecimalsModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsModulationRate();
    return -1;
}

///проверяет, что скорость модуляции не выходит за допустимые границы
bool Generator::isValidModulationRate(const double &rate) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidModulationRate(rate);
    return false;
}

///устанавливает скорость модуляции
bool Generator::setModulationRate(const double &rate) const
{
    if (!isValidModulationRate(rate)) //
        return false;
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationRate(rate);
    return false;
}

///возвращает скорость модуляции
double Generator::getModulationRate() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationRate();
    return -1;
}

///проверяет возможность работы с интервалом/глубиной модуляции
bool Generator::workWithModulationSpan() const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return true;
    return false;
}

///возвращает интервал/глубину по умолчанию
double Generator::getDefaultModulationSpan() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinModulationSpan(getDefaultFunction());
    return -1;
}

///устанавливает интервал/глубину по умолчанию
bool Generator::setDefaultModulationSpan() const
{
    return setModulationSpan(getDefaultModulationSpan());
}

///возвращает минимальное интервал/глубину
double Generator::getMinModulationSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinModulationSpan(waveform);
    return -1;
}

///возвращает минимальную интервал/глубину, при этом сам определяет, какая сейчас Function==waveform
double Generator::getMinModulationSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMinModulationSpan(getFunction());
    return -1;
}

///возвращает максимальную интервал/глубину
double Generator::getMaxModulationSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxModulationSpan(waveform);
    return -1;
}

///возвращает максимальную интервал/глубину, при этом сам определяет, какая сейчас Function==waveform
double Generator::getMaxModulationSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getMaxModulationSpan(getFunction());
    return -1;
}

///возвращает шаг интервал/глубины
double Generator::getStepModulationSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getStepModulationSpan(waveform);
    return -1;
}

///возвращает шаг интервал/глубины, при этом сам определяет, какая сейчас Function==waveform
double Generator::getStepModulationSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getStepModulationSpan(getFunction());
    return -1;
}

///∂ что это?
double Generator::getDecimalsModulationSpan(const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsModulationSpan(waveform);
    return -1;
}

///∂ что это?, при этом сам определяет, какая сейчас Function==waveform
double Generator::getDecimalsModulationSpanCurrent() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getDecimalsModulationSpan(getFunction());
    return -1;
}

/// проверяет, что интервал/глубина для заданной формы сигнала не выходит за допустимые границы
bool Generator::isValidModulationSpan(const double &span, const std::string &waveform) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidModulationSpan(span, waveform);
    return false;
}

/// проверяет, что интервал/глубина для заданной формы сигнала не выходит за допустимые границы, при этом сам определяет, какая сейчас Function==waveform
/// \brief Собственная разработка для проверки на адекватную величину (внутри допустимого диапазона) для функции setAmplitude
bool Generator::isValidModulationSpan(const double &span) const
{
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->isValidModulationSpan(span, getFunction());
    return false;
}

///устанавливает интервал/глубину
bool Generator::setModulationSpan(const double &span) const
{
    if (!isValidModulationSpan(span)) //
        return false;
    if (this->generatorModel == "DS335")
        return false;
    if (this->generatorModel == "DS345")
        return this->ds345->setModulationSpan(span);
    return false;
}

///возвращает интервал/глубину
double Generator::getModulationSpan() const
{
    if (this->generatorModel == "DS335")
        return -1;
    if (this->generatorModel == "DS345")
        return this->ds345->getModulationSpan();
    return -1;
}
