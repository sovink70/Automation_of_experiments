#include "DS345.h"

DS345::DS345()
{
    this->serial = nullptr;
    this->srs = nullptr;

    init();
}

//DS345::DS345(const QString &portName, const int &baudrate, const int &stopBit, const int &parity)
//{
//    this->serial = nullptr;
//    this->srs = nullptr;

//    init();

//∂пока уберём -  проверка того, что он законнектился
//    setConnection(portName, baudrate, stopBit, parity);
//}

DS345::~DS345()
{
//    if (this->serial->isOpen())
//        this->serial->close();
//    this->serial->~QSerialPort();
//    delete this->serial;
//    this->serial = nullptr;

//    this->srs->~SRS();
//    delete this->srs;
//    this->srs = nullptr;
}


void DS345::initBaudrateList()
{
    this->baudrateList.clear();

    this->baudrateList.push_back("1200");
    this->baudrateList.push_back("2400");
    this->baudrateList.push_back("4800");
    this->baudrateList.push_back("9600");

    return;
}

std::vector<std::string> DS345::getBaudrateList() const
{
    return this->baudrateList;
}

bool DS345::isValidBaudrate(const int &baudrate) const
{
    return isValidString(this->baudrateList, std::to_string(baudrate) ); //QString::number(baudrate)
}

bool DS345::changeBaudrate(const int &baudrate)
{
    if (!isValidBaudrate(baudrate))
        return false;

    if (!this->serial->isOpen()) {
        this->serial->setBaudRate((qint32) baudrate);
        return true;
    } else {
        this->serial->close();
        //∂ return setConnection(this->serial->portName(), baudrate);
    }
}

void DS345::setWriteTimeout(const int &new_writeTimeout)
{
    return this->srs->setWriteTimeout(new_writeTimeout);
}

int DS345::getWriteTimeout() const
{
    return this->srs->getWriteTimeout();
}

void DS345::setReadTimeout(const int &new_readTimeout)
{
    return this->srs->setReadTimeout(new_readTimeout);
}

int DS345::getReadTimeout() const
{
    return this->srs->getReadTimeout();
}

void DS345::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    return this->srs->setReadWaitTimeout(new_readWaitTimeout);
}

int DS345::getReadWaitTimeout() const
{
    return this->srs->getReadWaitTimeout();
}


//∂ нужные 4 ф-ции- целиком ссылаются на SRS НАДО убрать Qstring - СКАТАТЬ У ЛЁШИ-ВИТИ
//int DS345::numberFromString(const QStringList &list, const QString &string) const
//{
//    return this->srs->numberFromString(list, string);
//}

//QString DS345::stringFromNumber(const QStringList &list, const int &number) const
//{
//    return this->srs->stringFromNumber(list, number);
//}

//bool DS345::isValidString(const QStringList &list, const QString &string) const
//{
//    return this->srs->isValidString(list, string);
//}

//bool DS345::isValidNumber(const QStringList &list, const int &number) const
//{
//    return this->srs->isValidNumber(list, number);
//}
//

//∂ СКАТАНО
int DS345::numberFromString(const std::vector < std::string > &vector, const std::string &string) const {
    for(size_t i = 0 ; i < vector.size(); ++i) {
        if (vector[i] == string)
            return static_cast<int>(i);
    }
    return -1;
}

std::string DS345::stringFromNumber(const std::vector < std::string > &vector, const int &number) const{
    if (isValidNumber(vector, number))
        return vector.at(static_cast<size_t>(number));
    return "";
}

bool DS345::isValidString(const std::vector< std::string> &vector, const std::string &string) const {
    return(numberFromString(vector, string) != -1);
}

bool DS345::isValidNumber(const std::vector< std::string> &vector, const int &number) const {
    return (number >= 0 && number < static_cast<int>(vector.size()));
}
//

void DS345::initAmplitudeTypeList()
{
    this->amplitudeTypeList.clear();

    this->amplitudeTypeList.push_back("VP");
    this->amplitudeTypeList.push_back("VR");
    this->amplitudeTypeList.push_back("DB");

    return;
}

// было QStringList
std::vector<std::string> DS345::getAmplitudeTypeList() const
{
   return this->amplitudeTypeList;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMinAmplitude(const string &waveform, const string &unit) const
{
    if (waveform == "SINE") {
        if (unit == "VP")
            return this->minAmplitudeSineVpp;
        if (unit == "VR")
            return this->minAmplitudeSineVrms;
        if (unit == "DB")
            return this->minAmplitudeSinedBm;
    }
    if (waveform == "SQUARE") {
        if (unit == "VP")
            return this->minAmplitudeSquareVpp;
        if (unit == "VR")
            return this->minAmplitudeSquareVrms;
        if (unit == "DB")
            return this->minAmplitudeSquaredBm;
    }
    if (waveform == "TRIANGLE") {
        if (unit == "VP")
            return this->minAmplitudeTriangleVpp;
        if (unit == "VR")
            return this->minAmplitudeTriangleVrms;
        if (unit == "DB")
            return this->minAmplitudeTriangledBm;
    }
    if (waveform == "RAMP") {
        if (unit == "VP")
            return this->minAmplitudeRampVpp;
        if (unit == "VR")
            return this->minAmplitudeRampVrms;
        if (unit == "DB")
            return this->minAmplitudeRampdBm;
    }
    if (waveform == "NOISE") {
        if (unit == "VP")
            return this->minAmplitudeNoiseVpp;
        if (unit == "VR")
            return this->minAmplitudeNoiseVrms;
        if (unit == "DB")
            return this->minAmplitudeNoisedBm;
    }
    if (waveform == "ARBITRARY") {
        if (unit == "VP")
            return this->minAmplitudeArbitraryVpp;
        if (unit == "VR")
            return -1;
        if (unit == "DB")
            return -1;
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMaxAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (waveform == "SINE") {
        if (unit == "VP")
            return this->maxAmplitudeSineVpp;
        if (unit == "VR")
            return this->maxAmplitudeSineVrms;
        if (unit == "DB")
            return this->maxAmplitudeSinedBm;
    }
    if (waveform == "SQUARE") {
        if (unit == "VP")
            return this->maxAmplitudeSquareVpp;
        if (unit == "VR")
            return this->maxAmplitudeSquareVrms;
        if (unit == "DB")
            return this->maxAmplitudeSquaredBm;
    }
    if (waveform == "TRIANGLE") {
        if (unit == "VP")
            return this->maxAmplitudeTriangleVpp;
        if (unit == "VR")
            return this->maxAmplitudeTriangleVrms;
        if (unit == "DB")
            return this->maxAmplitudeTriangledBm;
    }
    if (waveform == "RAMP") {
        if (unit == "VP")
            return this->maxAmplitudeRampVpp;
        if (unit == "VR")
            return this->maxAmplitudeRampVrms;
        if (unit == "DB")
            return this->maxAmplitudeRampdBm;
    }
    if (waveform == "NOISE") {
        if (unit == "VP")
            return this->maxAmplitudeNoiseVpp;
        if (unit == "VR")
            return this->maxAmplitudeNoiseVrms;
        if (unit == "DB")
            return this->maxAmplitudeNoisedBm;
    }
    if (waveform == "ARBITRARY") {
        if (unit == "VP")
            return this->maxAmplitudeArbitraryVpp;
        if (unit == "VR")
            return -1;
        if (unit == "DB")
            return -1;
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getStepAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (waveform == "SINE") {
        if (unit == "VP")
            return this->stepAmplitudeSineVpp;
        if (unit == "VR")
            return this->stepAmplitudeSineVrms;
        if (unit == "DB")
            return this->stepAmplitudeSinedBm;
    }
    if (waveform == "SQUARE") {
        if (unit == "VP")
            return this->stepAmplitudeSquareVpp;
        if (unit == "VR")
            return this->stepAmplitudeSquareVrms;
        if (unit == "DB")
            return this->stepAmplitudeSquaredBm;
    }
    if (waveform == "TRIANGLE") {
        if (unit == "VP")
            return this->stepAmplitudeTriangleVpp;
        if (unit == "VR")
            return this->stepAmplitudeTriangleVrms;
        if (unit == "DB")
            return this->stepAmplitudeTriangledBm;
    }
    if (waveform == "RAMP") {
        if (unit == "VP")
            return this->stepAmplitudeRampVpp;
        if (unit == "VR")
            return this->stepAmplitudeRampVrms;
        if (unit == "DB")
            return this->stepAmplitudeRampdBm;
    }
    if (waveform == "NOISE") {
        if (unit == "VP")
            return this->stepAmplitudeNoiseVpp;
        if (unit == "VR")
            return this->stepAmplitudeNoiseVrms;
        if (unit == "DB")
            return this->stepAmplitudeNoisedBm;
    }
    if (waveform == "ARBITRARY") {
        if (unit == "VP")
            return this->stepAmplitudeArbitraryVpp;
        if (unit == "VR")
            return -1;
        if (unit == "DB")
            return -1;
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getDecimalsAmplitude(const std::string &waveform, const std::string &unit) const
{
    if (waveform == "SINE") {
        if (unit == "VP")
            return this->decimalsAmplitudeSineVpp;
        if (unit == "VR")
            return this->decimalsAmplitudeSineVrms;
        if (unit == "DB")
            return this->decimalsAmplitudeSinedBm;
    }
    if (waveform == "SQUARE") {
        if (unit == "VP")
            return this->decimalsAmplitudeSquareVpp;
        if (unit == "VR")
            return this->decimalsAmplitudeSquareVrms;
        if (unit == "DB")
            return this->decimalsAmplitudeSquaredBm;
    }
    if (waveform == "TRIANGLE") {
        if (unit == "VP")
            return this->decimalsAmplitudeTriangleVpp;
        if (unit == "VR")
            return this->decimalsAmplitudeTriangleVrms;
        if (unit == "DB")
            return this->decimalsAmplitudeTriangledBm;
    }
    if (waveform == "RAMP") {
        if (unit == "VP")
            return this->decimalsAmplitudeRampVpp;
        if (unit == "VR")
            return this->decimalsAmplitudeRampVrms;
        if (unit == "DB")
            return this->decimalsAmplitudeRampdBm;
    }
    if (waveform == "NOISE") {
        if (unit == "VP")
            return this->decimalsAmplitudeNoiseVpp;
        if (unit == "VR")
            return this->decimalsAmplitudeNoiseVrms;
        if (unit == "DB")
            return this->decimalsAmplitudeNoisedBm;
    }
    if (waveform == "ARBITRARY") {
        if (unit == "VP")
            return this->decimalsAmplitudeArbitraryVpp;
        if (unit == "VR")
            return -1;
        if (unit == "DB")
            return -1;
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &unit) const
{
    if (!isValidAmplitudeType(unit))
        return false;
    return (getMinAmplitude(waveform, unit) <= amplitude &&
            amplitude <= getMaxAmplitude(waveform, unit));
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::isValidAmplitudeType(const std::string &unit) const
{
    return isValidString(this->amplitudeTypeList, unit);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::setAmplitude(const double &amplitude, const std::string &unit) const
{
    if (!isValidAmplitudeType(unit))
        return false;

    std::string command = "AMPL " + std::to_string(amplitude) + "" + unit; //    " + QString::number(amplitude) + .... ;

    return sendCommand(command);
}

//действуем по аналогии. Но оборачивать в структуру commands https://github.com/vicvict/Lock-In-Amplifier/blob/c636a45a072afa827e81103b149dd8042f3c8058/SerialPortCommunicationQt/SerialPortCommunication/SRS/LockInAmplifier/lockinamplifier.h#L41 , как у ребят, мне лень
//bool LockInAmplifier::setInputVoltageMode(const int &inputVoltageMode) const {
//    if (!isValidNumber(this->inputVoltageMode, inputVoltageMode))
//        return false;
//    std::string command = commands.InputVoltageMode + separator + std::to_string(inputVoltageMode);
//    return sendCommand(command);
//}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
std::string DS345::getAmplitude(const std::string &unit) const
{
    if (!isValidAmplitudeType(unit)) //if !a <=> if a==0
        return "-1";
    std::string response;
    std::string command = "AMPL" + query_suffix + separator + unit;
    if (!sendQuery(command, response))
        return "-1";
    else
//        std::string  = ask(commands.Frequence + "INT" + query_suffix);
        return response;
//    return response.trimmed().left(response.length() - 2).toDouble();
}

//std::string LockInAmplifier:: getInternalFrequency() const {
//    std::string answer = ask(commands.Frequence + "INT" + query_suffix);
//    return answer;
//}

double DS345::getMinOffset() const
{
    return this->minOffsetV;
}

double DS345::getMaxOffset() const
{
    return this->maxOffsetV;
}

double DS345::getStepOffset() const
{
    return this->stepOffsetV;
}

double DS345::getDecimalsOffset() const
{
    return this->decimalsOffsetV;
}

bool DS345::isValidOffset(const double &offset) const
{
    return (this->minOffsetV <= offset && offset <= this->maxOffsetV);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::setOffset(const double &offset) const
{
    if (!isValidOffset(offset))
        return false;

    std::string command = "OFFS " + std::to_string(offset); //     std::string command = "AMPL " + std::to_string(amplitude) + "" + unit; // command = "OFFS " + QString::number(offset);
    return sendCommand(command);
}

string DS345::getOffset() const
{
    return ask("OFFS?"); // пока решили выводить по максимому в ответ не double, а  string // .toDouble();
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMinFrequency(const std::string &waveform) const
{
    if (waveform == "SINE")
        return this->minFrequencySine;
    if (waveform == "SQUARE")
        return this->minFrequencySquare;
    if (waveform == "TRIANGLE")
        return this->minFrequencyTriangle;
    if (waveform == "RAMP")
        return this->minFrequencyRamp;
    if (waveform == "NOISE")
        return this->minFrequencyNoise;
    if (waveform == "ARBITRARY")
        return this->minFrequencyArbitrary;

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMaxFrequency(const std::string &waveform) const
{
    if (waveform == "SINE")
        return this->maxFrequencySine;
    if (waveform == "SQUARE")
        return this->maxFrequencySquare;
    if (waveform == "TRIANGLE")
        return this->maxFrequencyTriangle;
    if (waveform == "RAMP")
        return this->maxFrequencyRamp;
    if (waveform == "NOISE")
        return this->maxFrequencyNoise;
    if (waveform == "ARBITRARY")
        return this->maxFrequencyArbitrary;

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getStepFrequency(const std::string &waveform) const
{
    if (waveform == "SINE")
        return this->stepFrequencySine;
    if (waveform == "SQUARE")
        return this->stepFrequencySquare;
    if (waveform == "TRIANGLE")
        return this->stepFrequencyTriangle;
    if (waveform == "RAMP")
        return this->stepFrequencyRamp;
    if (waveform == "NOISE")
        return this->stepFrequencyNoise;
    if (waveform == "ARBITRARY")
        return this->stepFrequencyArbitrary;

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getDecimalsFrequency(const std::string &waveform) const
{
    if (waveform == "SINE")
        return this->decimalsFrequencySine;
    if (waveform == "SQUARE")
        return this->decimalsFrequencySquare;
    if (waveform == "TRIANGLE")
        return this->decimalsFrequencyTriangle;
    if (waveform == "RAMP")
        return this->decimalsFrequencyRamp;
    if (waveform == "NOISE")
        return this->decimalsFrequencyNoise;
    if (waveform == "ARBITRARY")
        return this->decimalsFrequencyArbitrary;

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::isValidFrequency(const double &frequency, const std::string &waveform) const
{
    return (getMinFrequency(waveform) <= frequency && frequency <= getMaxFrequency(waveform));
}

//∂напрягает В каком виде он выведет частоту потому что передаётся три аргумента
bool DS345::setFrequency(const double &frequency) const
{
    std::string command = "FREQ " + std::to_string(frequency); // QString::number(frequency,'f',8);
    return sendCommand(command);
}

std::string DS345::getFrequency() const
{
    return ask("FREQ?"); // .toDouble();
}

void DS345::initFunctionList()
{
    this->functionList.clear();

    this->functionList.push_back("SINE");
    this->functionList.push_back("SQUARE");
    this->functionList.push_back("TRIANGLE");
    this->functionList.push_back("RAMP");
    this->functionList.push_back("NOISE");
    this->functionList.push_back("ARBITRARY");

    return;
}

std::vector<std::string> DS345::getFunctionList() const
{
    return this->functionList;
}

//∂НУЖНЫЕ!!ещё 2 нужные ф-ции-  НАДО убрать Qstring - СКАТАТЬ У ЛЁШИ-ВИТИ
int DS345::functionNumberFromString(const std::string &function_string) const
{
    return numberFromString(this->functionList, function_string);
}

//НУЖНЫЕ? ещё 2 нужные ф-ции- НАДО убрать Qstring - СКАТАТЬ У ЛЁШИ-ВИТИ
string DS345::functionStringFromNumber(const int &function_number) const
{
    return stringFromNumber(this->functionList, function_number);
}

bool DS345::setFunction(const int &function) const
{
    if (!isValidNumber(this->functionList, function))
        return false;

    std::string command = "FUNC " + std::to_string(function);
    return sendCommand(command);
}

bool DS345::setFunction(const std::string &function) const
{
    return setFunction(functionNumberFromString(function));
}

std::string DS345::getFunction() const
{
    return ask("FUNC?"); //functionStringFromNumber(ask("FUNC?").toInt());
}

bool DS345::setInverse(const bool &inverse) const
{
    std::string command = "INVT ";
    if (inverse)
        command += "1";
    else
        command += "0";
    return sendCommand(command);
}

//мне bool непривычен, проще string integer
std::string DS345::getInverse() const
{
    //return (ask("INVT?").toInt() == 1);
    return ask("INVT?");
}
//bool DS345::getInverse() const
//{
//    //return (ask("INVT?").toInt() == 1);
//    return (stoi(ask("INVT?")) == 1);
//}

int DS345::getMinAMDepth() const
{
    return this->minAMDepth;
}

int DS345::getMaxAMDepth() const
{
    return this->maxAMDepth;
}

bool DS345::isValidAMDepth(const int &persentage) const
{
    return (this->minAMDepth <= persentage && persentage <= this->maxAMDepth);
}

bool DS345::setAMdepth(const int &persentage) const
{
    if (!isValidAMDepth(persentage))
        return false;

    std::string command = "DPTH " + std::to_string(persentage);
    return sendCommand(command);
}

std::string DS345::getAMdepth() const //int
{
    return ask("DPTH?"); // ask("DPTH?").toInt();
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform в string чтобы их можно было пихать сюда
double DS345::getMinFMSpan(const std::string &waveform) const
{
    return getMinFrequency(waveform);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMaxFMSpan(const std::string &waveform) const
{
    return getMaxFrequency(waveform);
}

bool DS345::isValidFMSpan(const int &span, const std::string &waveform) const
{
    return (getMinFMSpan(waveform) <= span && span <= getMaxFMSpan(waveform));
}

bool DS345::setFMSpan(const double &span) const
{
    std::string command = "FDEV " + std::to_string(span);
    return sendCommand(command);
}

std::string DS345::getFMSpan() const
{
    return ask("FDEV?"); //.toDouble();
}

void DS345::initModulationFunctionList()
{
    this->modulationFunctionList.clear();

    this->modulationFunctionList.push_back("SINGLE SWEEP");
    this->modulationFunctionList.push_back("RAMP");
    this->modulationFunctionList.push_back("TRIANGLE");
    this->modulationFunctionList.push_back("SINE");
    this->modulationFunctionList.push_back("SQUARE");
    this->modulationFunctionList.push_back("ARB");
    this->modulationFunctionList.push_back("NONE");

    return;
}

std::vector<std::string> DS345::getModulationFunctionList() const
{
    return this->modulationFunctionList;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
int DS345::modulationFunctionNumberFromString(const std::string &function_string) const
{
    return numberFromString(this->modulationFunctionList, function_string);
}

string DS345::modulationFunctionStringFromNumber(const int &function_number) const
{
    return stringFromNumber(this->modulationFunctionList, function_number);
}

bool DS345::setModulationFunction(const int &function) const
{
    if (!isValidNumber(this->modulationFunctionList, function))
        return false;

    std::string command = "MDWF " + std::to_string(function);
    return sendCommand(command);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::setModulationFunction(const std::string &function) const
{
    return setModulationFunction(modulationFunctionNumberFromString(function));
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
std::string DS345::getModulationFunction() const
{
    return ask("MDWF?"); //modulationFunctionStringFromNumber(ask("MDWF?").toInt());
}

bool DS345::setModulationEnabled(const bool &enable) const
{
    std::string command = "MENA ";
    if (enable)
        command += "1";
    else
        command += "0";
    return sendCommand(command);
}

//мне bool непривычен, проще string integer
std::string DS345::getModulationEnabled() const
{
    return ask("MENA?");
    //return (ask("MENA?").toInt() == 1);
}

void DS345::initModulationTypeList()
{
    this->modulationTypeList.clear();

    this->modulationTypeList.push_back("LIN SWEEP");
    this->modulationTypeList.push_back("LOG SWEEP");
    this->modulationTypeList.push_back("INTERNAL AM");
    this->modulationTypeList.push_back("FM");
    this->modulationTypeList.push_back("FiM");
    this->modulationTypeList.push_back("BURST");

    return;
}

// // было QStringList
std::vector<std::string> DS345::getModulationTypeList() const
{
    return this->modulationTypeList;
}

int DS345::modulationTypeNumberFromString(const std::string &type_string) const
{
    return numberFromString(this->modulationTypeList, type_string);
}

std::string DS345::modulationTypeStringFromNumber(const int &type_number) const
{
    return stringFromNumber(this->modulationTypeList, type_number);
}

bool DS345::setModulationType(const int &type) const
{
    if (!isValidNumber(this->modulationTypeList, type))
        return false;

    std::string command = "MTYP " + std::to_string(type);
    return sendCommand(command);
}

bool DS345::setModulationType(const std::string &type) const
{
    return setModulationType(modulationTypeNumberFromString(type));
}


std::string DS345::getModulationType() const
{
    return ask("MTYP?"); //modulationTypeStringFromNumber(ask("MTYP?").toInt());
}

double DS345::getMinModulationRate() const
{
    return this->minModulationRate;
}

double DS345::getMaxModulationRate() const
{
    return this->maxModulationRate;
}

double DS345::getStepModulationRate() const
{
    return this->stepModulationRate;
}

double DS345::getDecimalsModulationRate() const
{
    return this->decimalsModulationRate;
}

bool DS345::isValidModulationRate(const double &rate) const
{
    return (this->minModulationRate <= rate && rate <= this->maxModulationRate);
}

bool DS345::setModulationRate(const double &rate) const
{
    if (!isValidModulationRate(rate))
        return false;

    std::string command = "RATE " + std::to_string(rate);
    return sendCommand(command);

}

std::string DS345::getModulationRate() const
{
    return ask("RATE?"); //.toDouble();
}

double DS345::getMinModulationSpan(const std::string &waveform) const
{
    return getMinFrequency(waveform);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMaxModulationSpan(const std::string &waveform) const
{
    return getMaxFrequency(waveform);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getStepModulationSpan(const std::string &waveform) const
{
    return getStepFrequency(waveform);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getDecimalsModulationSpan(const std::string &waveform) const
{
    return getDecimalsFrequency(waveform);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS345::isValidModulationSpan(const double &span, const std::string &waveform) const
{
    return (getMinModulationSpan(waveform) <= span && span <= getMaxModulationSpan(waveform));
}

bool DS345::setModulationSpan(const double &span) const
{
    std::string command = "SPAN " + std::to_string(span);
    return sendCommand(command);
}

std::string DS345::getModulationSpan() const
{
    return ask("SPAN?"); //.toDouble();
}


//ИЛИ НЕ ДОЛЖЕНБ ЭТИ сигналы наверное фича чисто QSERIALPORT

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//void DS345::catchErrorSignal(const std::string &s) const
//{
//    emit this->errorSignal(s);
//}

//// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//void DS345::catchResponseSignal(const std::string &s) const
//{
//    emit this->responseSignal(s);
//}

//// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//void DS345::catchCommandSignal(const std::string &s) const
//{
//    emit this->commandSignal(s);
//}

//// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//void DS345::catchTimeoutSignal(const std::string &s) const
//{
//    emit this->timeoutSignal(s);
//}
