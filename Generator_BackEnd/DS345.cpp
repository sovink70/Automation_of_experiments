#include "DS345.h"

DS345::DS345()
{
    this->serial = nullptr;
    this->srs = nullptr;

    init();
}

DS345::~DS345()
{

}


void DS345::initAmplitudeTypeList()
{
    this->amplitudeTypeList.clear();

    this->amplitudeTypeList.push_back("VP");
    this->amplitudeTypeList.push_back("VR");
    this->amplitudeTypeList.push_back("DB");

    return;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS345::getMinAmplitude(const std::string &waveform, const std::string &unit) const
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

    std::string command = "DPTH" + separator + std::to_string(persentage);
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
    std::string command = "FDEV" + separator + std::to_string(span);
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

std::string DS345::modulationFunctionStringFromNumber(const int &function_number) const
{
    return stringFromNumber(this->modulationFunctionList, function_number);
}

bool DS345::setModulationFunction(const int &function) const
{
    if (!isValidNumber(this->modulationFunctionList, function))
        return false;

    std::string command = "MDWF" + separator + std::to_string(function);
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
    std::string command = "MENA" + separator;
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

    std::string command = "MTYP" + separator + std::to_string(type);
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

    std::string command = "RATE" + separator + std::to_string(rate);
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
    std::string command = "SPAN" + separator + std::to_string(span);
    return sendCommand(command);
}

std::string DS345::getModulationSpan() const
{
    return ask("SPAN?"); //.toDouble();
}
