#include "SRSgenerator.h"

void SRSGenerator::initBaudrateList()
{
    this->baudrateList.clear();

    this->baudrateList.push_back("1200");
    this->baudrateList.push_back("2400");
    this->baudrateList.push_back("4800");
    this->baudrateList.push_back("9600");

    return;
}

std::vector<std::string> SRSGenerator::getBaudrateList() const
{
    return this->baudrateList;
}

bool SRSGenerator::isValidBaudrate(const int &baudrate) const
{
    return isValidString(this->baudrateList, std::to_string(baudrate) ); //QString::number(baudrate)
}

//∂ для этого есть setBaudrate в SerialPortCommunicationQt
//bool DS355SRSGenerator::changeBaudrate(const int &baudrate)
//{
//    if (!isValidBaudrate(baudrate))
//        return false;

//    if (!this->serial->isOpen()) {
//        this->serial->setBaudRate((qint32) baudrate);
//        return true;
//    } else {
//        this->serial->close();
//        return setConnection(this->serial->portName(), baudrate);
//    }
//}

void SRSGenerator::setWriteTimeout(const int &new_writeTimeout)
{
    return this->srs->setWriteTimeout(new_writeTimeout);
}

int SRSGenerator::getWriteTimeout() const
{
    return this->srs->getWriteTimeout();
}

void SRSGenerator::setReadTimeout(const int &new_readTimeout)
{
    return this->srs->setReadTimeout(new_readTimeout);
}

int SRSGenerator::getReadTimeout() const
{
    return this->srs->getReadTimeout();
}

void SRSGenerator::setReadWaitTimeout(const int &new_readWaitTimeout)
{
    return this->srs->setReadWaitTimeout(new_readWaitTimeout);
}

int SRSGenerator::getReadWaitTimeout() const
{
    return this->srs->getReadWaitTimeout();
}


int SRSGenerator::numberFromString(const std::vector < std::string > &vector, const std::string &string) const {
    for(size_t i = 0 ; i < vector.size(); ++i) {
        if (vector[i] == string)
            return static_cast<int>(i);
    }
    return -1;
}

std::string SRSGenerator::stringFromNumber(const std::vector < std::string > &vector, const int &number) const{
    if (isValidNumber(vector, number))
        return vector.at(static_cast<size_t>(number));
    return "";
}

bool SRSGenerator::isValidString(const std::vector< std::string> &vector, const std::string &string) const {
    return(numberFromString(vector, string) != -1);
}

bool SRSGenerator::isValidNumber(const std::vector< std::string> &vector, const int &number) const {
    return (number >= 0 && number < static_cast<int>(vector.size()));
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//∂взял из DS 345 - штука нужная. НАДО РЕАЛИЗОВАТЬ везде, вместо bool
/// проверяет, что отправлена правильная единица измерения амплитуды сигнала
bool SRSGenerator::isValidAmplitudeType(const std::string &unit) const
{
    return isValidString(this->amplitudeTypeList, unit);
}

//∂ почему-то неуверен, что это можно сделать общим. Но сделаю
std:: vector< std:: string> SRSGenerator::getAmplitudeTypeList() const
{
   return this->amplitudeTypeList;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
//∂ а может сразу величину амплитуды в виде стринга пихать? ∂∂ вообще надо пройтись по всяким to_string stod ... насколько их использование оправдано
///устанавливает амплитуду
bool SRSGenerator::setAmplitude(const double &amplitude, const std::string &unit) const
{
    if (!isValidAmplitudeType(unit))
        return false;
    std::string command = "AMPL" + separator + std::to_string(amplitude) + unit; //    " + QString::number(amplitude) + .... ;
    return sendCommand(command);
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
///возвращает амплитуду
std::string SRSGenerator::getAmplitude(const std::string &unit) const
{
   if (!isValidAmplitudeType(unit)) //if !a <=> if a==0
        return "-1";
   std::string response;
    std::string command = "AMPL" + query_suffix + separator + unit;
    if (!sendQuery(command, response))
    return "-1";
    else
        return response;
}

///возвращает минимальное смещение
double SRSGenerator::getMinOffset() const
{
    return this->minOffsetV;
}

double SRSGenerator::getMaxOffset() const
{
    return this->maxOffsetV;
}

double SRSGenerator::getStepOffset() const
{
    return this->stepOffsetV;
}

double SRSGenerator::getDecimalsOffset() const
{
    return this->decimalsOffsetV;
}

bool SRSGenerator::isValidOffset(const double &offset) const
{
    return (this->minOffsetV <= offset && offset <= this->maxOffsetV);
}

bool SRSGenerator::setOffset(const double &offset) const
{
    if (!isValidOffset(offset))
        return false;
    std::string command = "OFFS" + separator + std::to_string(offset);
    return sendCommand(command);
}

std::string SRSGenerator::getOffset() const
{
    return ask("OFFS?"); //.toDouble(); / пока решили выводить по максимому в ответ не double, а  string // .toDouble();

}



//∂напрягает В каком виде он выведет частоту потому что передаётся три аргумента
bool SRSGenerator::setFrequency(const double &frequency) const
{
    std::string command = "FREQ" + separator + std::to_string(frequency); // QString::number(frequency,'f',8);
    return sendCommand(command);
}

std::string SRSGenerator::getFrequency() const
{
    return ask("FREQ?");// toDouble();
}

std::vector<std::string> SRSGenerator::getFunctionList() const
{
    return this->functionList;
}

int SRSGenerator::functionNumberFromString(const std::string &function_string) const
{
    return numberFromString(this->functionList, function_string);
}

std::string SRSGenerator::functionStringFromNumber(const int &function_number) const
{
    return stringFromNumber(this->functionList, function_number);
}

bool SRSGenerator::setFunction(const int &function) const
{
    if (!isValidNumber(this->functionList, function))
        return false;

    std::string command = "FUNC" + separator + std::to_string(function);
    return sendCommand(command);
}

bool SRSGenerator::setFunction(const std::string &function) const
{
    return setFunction(functionNumberFromString(function));
}

std::string SRSGenerator::getFunction() const
{
    return ask("FUNC?"); //functionStringFromNumber(ask("FUNC?").toInt());
}

bool SRSGenerator::setInverse(const bool &inverse) const
{
    std::string command = "INVT" + separator;
    if (inverse)
        command += "1";
    else
        command += "0";
    return sendCommand(command);
}

//мне bool непривычен, проще string integer
std::string SRSGenerator::getInverse() const
{
    //return (ask("INVT?").toInt() == 1);
    return ask("INVT?");
}
