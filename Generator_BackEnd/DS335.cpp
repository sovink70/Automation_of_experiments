#include "DS335.h"

//#include <cctype> - это я мучался с toUpper

DS335::DS335()
{
    this->serial = nullptr;
    this->srs = nullptr;

    init();
}

DS335::~DS335()
{

}

void DS335::initAmplitudeTypeList()
{
    this->amplitudeTypeList.clear();

    this->amplitudeTypeList.push_back("VP");
    this->amplitudeTypeList.push_back("VR");

    return;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getMinAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const //bool &VRMS
{
    //∂ достаточно костыльно попытался заменить  для Qstring/ не понимаю, зачем вообще так делать - можно же сразу в верхнем регистре писать
    // учитывая то, что дальше обходятся без него - предлагаю вообще убрать
//    if (outputZ.toUpper() == "50OHMS") {
//    std::string str;
//    for (std::string::size_type i=0; i<outputZ.length(); i++)
//        str[i] = toupper(outputZ[i]);
//    if (str == "50OHMS") {
    if (outputZ == "50OHMS") {
        if (waveform == "SINE") {
            if (unit == "VR") //(VRMS)
                return this->minAmplitude50OhmsSineVrms;
            if (unit == "VP") //else
                return this->minAmplitude50OhmsSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->minAmplitude50OhmsSquareVrms;
            if (unit == "VP")
                return this->minAmplitude50OhmsSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->minAmplitude50OhmsTriangleVrms;
            if (unit == "VP")
                return this->minAmplitude50OhmsTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->minAmplitude50OhmsRampVrms;
            if (unit == "VP")
                return this->minAmplitude50OhmsRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->minAmplitude50OhmsNoiseVrms;
            if (unit == "VP")
                return this->minAmplitude50OhmsNoiseVpp;
        }
    } else {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->minAmplitudeHighZSineVrms;
            if (unit == "VP")
                return this->minAmplitudeHighZSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->minAmplitudeHighZSquareVrms;
            if (unit == "VP")
                return this->minAmplitudeHighZSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->minAmplitudeHighZTriangleVrms;
            if (unit == "VP")
                return this->minAmplitudeHighZTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->minAmplitudeHighZRampVrms;
            if (unit == "VP")
                return this->minAmplitudeHighZRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->minAmplitudeHighZNoiseVrms;
            if (unit == "VP")
                return this->minAmplitudeHighZNoiseVpp;
        }
    }

    return -1;
}

double DS335::getMaxAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (outputZ == "50OHMS") {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->maxAmplitude50OhmsSineVrms;
            if (unit == "VP")
                return this->maxAmplitude50OhmsSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->maxAmplitude50OhmsSquareVrms;
            if (unit == "VP")
                return this->maxAmplitude50OhmsSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->maxAmplitude50OhmsTriangleVrms;
            if (unit == "VP")
                return this->maxAmplitude50OhmsTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->maxAmplitude50OhmsRampVrms;
            if (unit == "VP")
                return this->maxAmplitude50OhmsRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->maxAmplitude50OhmsNoiseVrms;
            if (unit == "VP")
                return this->maxAmplitude50OhmsNoiseVpp;
        }
    } else {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->maxAmplitudeHighZSineVrms;
            if (unit == "VP")
                return this->maxAmplitudeHighZSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->maxAmplitudeHighZSquareVrms;
            if (unit == "VP")
                return this->maxAmplitudeHighZSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->maxAmplitudeHighZTriangleVrms;
            if (unit == "VP")
                return this->maxAmplitudeHighZTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->maxAmplitudeHighZRampVrms;
            if (unit == "VP")
                return this->maxAmplitudeHighZRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->maxAmplitudeHighZNoiseVrms;
            if (unit == "VP")
                return this->maxAmplitudeHighZNoiseVpp;
        }
    }

    return -1;
}

double DS335::getStepAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (outputZ == "50OHMS") {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->stepAmplitude50OhmsSineVrms;
            if (unit == "VP")
                return this->stepAmplitude50OhmsSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->stepAmplitude50OhmsSquareVrms;
            if (unit == "VP")
                return this->stepAmplitude50OhmsSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->stepAmplitude50OhmsTriangleVrms;
            if (unit == "VP")
                return this->stepAmplitude50OhmsTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->stepAmplitude50OhmsRampVrms;
            if (unit == "VP")
                return this->stepAmplitude50OhmsRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->stepAmplitude50OhmsNoiseVrms;
            if (unit == "VP")
                return this->stepAmplitude50OhmsNoiseVpp;
        }
    } else {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->stepAmplitudeHighZSineVrms;
            if (unit == "VP")
                return this->stepAmplitudeHighZSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->stepAmplitudeHighZSquareVrms;
            if (unit == "VP")
                return this->stepAmplitudeHighZSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->stepAmplitudeHighZTriangleVrms;
            if (unit == "VP")
                return this->stepAmplitudeHighZTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->stepAmplitudeHighZRampVrms;
            if (unit == "VP")
                return this->stepAmplitudeHighZRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->stepAmplitudeHighZNoiseVrms;
            if (unit == "VP")
                return this->stepAmplitudeHighZNoiseVpp;
        }
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getDecimalsAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const
{
    if (outputZ == "50OHMS") {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->decimalsAmplitude50OhmsSineVrms;
            if (unit == "VP")
                return this->decimalsAmplitude50OhmsSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->decimalsAmplitude50OhmsSquareVrms;
            if (unit == "VP")
                return this->decimalsAmplitude50OhmsSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->decimalsAmplitude50OhmsTriangleVrms;
            if (unit == "VP")
                return this->decimalsAmplitude50OhmsTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->decimalsAmplitude50OhmsRampVrms;
            if (unit == "VP")
                return this->decimalsAmplitude50OhmsRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->decimalsAmplitude50OhmsNoiseVrms;
            if (unit == "VP")
                return this->decimalsAmplitude50OhmsNoiseVpp;
        }
    } else {
        if (waveform == "SINE") {
            if (unit == "VR")
                return this->decimalsAmplitudeHighZSineVrms;
            if (unit == "VP")
                return this->decimalsAmplitudeHighZSineVpp;
        }
        if (waveform == "SQUARE") {
            if (unit == "VR")
                return this->decimalsAmplitudeHighZSquareVrms;
            if (unit == "VP")
                return this->decimalsAmplitudeHighZSquareVpp;
        }
        if (waveform == "TRIANGLE") {
            if (unit == "VR")
                return this->decimalsAmplitudeHighZTriangleVrms;
            if (unit == "VP")
                return this->decimalsAmplitudeHighZTriangleVpp;
        }
        if (waveform == "RAMP") {
            if (unit == "VR")
                return this->decimalsAmplitudeHighZRampVrms;
            if (unit == "VP")
                return this->decimalsAmplitudeHighZRampVpp;
        }
        if (waveform == "NOISE") {
            if (unit == "VR")
                return this->decimalsAmplitudeHighZNoiseVrms;
            if (unit == "VP")
                return this->decimalsAmplitudeHighZNoiseVpp;
        }
    }

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS335::isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &outputZ, const std::string &unit) const //bool &VRMS
{
    if (!isValidAmplitudeType(unit))
        return false;
    return (getMinAmplitude(waveform, outputZ, unit) <= amplitude &&
            amplitude <= getMaxAmplitude(waveform, outputZ, unit));
}



//не стал загонять в общак, чтобы нельзя было случайно выставить ARBITRARY, да и границы мин-макс у них разные
// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getMinFrequency(const std::string &waveform) const
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

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getMaxFrequency(const std::string &waveform) const
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

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getStepFrequency(const std::string &waveform) const
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

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
double DS335::getDecimalsFrequency(const std::string &waveform) const
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

    return -1;
}

// вот тут Артур должен привызове этой команды сразу же перевести QString &waveform, const QString &unit в string чтобы их можно было пихать сюда
bool DS335::isValidFrequency(const double &frequency, const std::string &waveform) const
{
    return (getMinFrequency(waveform) <= frequency && frequency <= getMaxFrequency(waveform));
}

void DS335::initFunctionList()
{
    this->functionList.clear();

    this->functionList.push_back("SINE");
    this->functionList.push_back("SQUARE");
    this->functionList.push_back("TRIANGLE");
    this->functionList.push_back("RAMP");
    this->functionList.push_back("NOISE");

    return;
}

bool DS335::setSynchronization(const bool &synchronization) const
{
    std::string command = "SYNC" + separator;
    if (synchronization)
        command += "1";
    else
        command += "0";
    return sendCommand(command);
}

bool DS335::getSynchronization() const
{
    return (ask("SYNC?") == "1"); //.toInt()
}

//Гоша сказал это не надо >> НАДО
void DS335::initOutputImpedanceList()
{
    this->outputImpedanceList.clear();

    this->outputImpedanceList.push_back("50OHMS");
    this->outputImpedanceList.push_back("Hi-Z");

    return;
}

std::vector<std::string> DS335::getOutputImpedanceList() const
{
    return this->outputImpedanceList;
}

int DS335::outputImpedanceNumberFromString(const std::string &outputImpedance_string) const
{
    return numberFromString(this->outputImpedanceList, outputImpedance_string);
}

std::string DS335::outputImpedanceStringFromNumber(const int &outputImpedance_number) const
{
    return stringFromNumber(this->outputImpedanceList, outputImpedance_number);
}

bool DS335::setOutputImpedance(const int &outputImpedance) const
{
    if (!isValidNumber(this->outputImpedanceList, outputImpedance))
        return false;

    std::string command = "TERM" + separator +  std::to_string(outputImpedance); //QString::number
    return sendCommand(command);
}

bool DS335::setOutputImpedance(const std::string &outputImpedance) const
{
    return setOutputImpedance(outputImpedanceNumberFromString(outputImpedance));
}

std::string DS335::getOutputImpedance() const
{
    return ask("TERM?"); // outputImpedanceStringFromNumber(ask("TERM?").toInt());
}
