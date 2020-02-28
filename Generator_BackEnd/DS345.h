#ifndef DS345_H
#define DS345_H

#include "SRSgenerator.h"

class DS345 : public SRSGenerator
{

private:
    const double maxAmplitudeSineVpp   = 10;
    const double minAmplitudeSineVpp   = 0.01;
    const double stepAmplitudeSineVpp  = 0.01;
    const int decimalsAmplitudeSineVpp = 3;

    const double maxAmplitudeSineVrms   = 3.54;
    const double minAmplitudeSineVrms   = 0.00354;
    const double stepAmplitudeSineVrms  = 0.01;
    const int decimalsAmplitudeSineVrms = 3;

    const double maxAmplitudeSinedBm   = +23.98;
    const double minAmplitudeSinedBm   = -36.02;
    const double stepAmplitudeSinedBm  = 0.01;
    const int decimalsAmplitudeSinedBm = 3;

    const double maxAmplitudeSquareVpp   = 10;
    const double minAmplitudeSquareVpp   = 0.01;
    const double stepAmplitudeSquareVpp  = 0.01;
    const int decimalsAmplitudeSquareVpp = 3;

    const double maxAmplitudeSquareVrms   = 5;
    const double minAmplitudeSquareVrms   = 0.005;
    const double stepAmplitudeSquareVrms  = 0.01;
    const int decimalsAmplitudeSquareVrms = 3;

    const double maxAmplitudeSquaredBm   = +26.99;
    const double minAmplitudeSquaredBm   = -33.0;
    const double stepAmplitudeSquaredBm  = 0.01;
    const int decimalsAmplitudeSquaredBm = 3;

    const double maxAmplitudeTriangleVpp   = 10;
    const double minAmplitudeTriangleVpp   = 0.01;
    const double stepAmplitudeTriangleVpp  = 0.01;
    const int decimalsAmplitudeTriangleVpp = 3;

    const double maxAmplitudeTriangleVrms   = 2.89;
    const double minAmplitudeTriangleVrms   = 0.00289;
    const double stepAmplitudeTriangleVrms  = 0.01;
    const int decimalsAmplitudeTriangleVrms = 3;

    const double maxAmplitudeTriangledBm   = +22.22;
    const double minAmplitudeTriangledBm   = -37.78;
    const double stepAmplitudeTriangledBm  = 0.01;
    const int decimalsAmplitudeTriangledBm = 3;

    const double maxAmplitudeRampVpp   = 10;
    const double minAmplitudeRampVpp   = 0.01;
    const double stepAmplitudeRampVpp  = 0.01;
    const int decimalsAmplitudeRampVpp = 3;

    const double maxAmplitudeRampVrms   = 2.89;
    const double minAmplitudeRampVrms   = 0.00289;
    const double stepAmplitudeRampVrms  = 0.01;
    const int decimalsAmplitudeRampVrms = 3;

    const double maxAmplitudeRampdBm   = +22.22;
    const double minAmplitudeRampdBm   = -37.78;
    const double stepAmplitudeRampdBm  = 0.01;
    const int decimalsAmplitudeRampdBm = 3;

    const double maxAmplitudeNoiseVpp   = 10;
    const double minAmplitudeNoiseVpp   = 0.01;
    const double stepAmplitudeNoiseVpp  = 0.01;
    const int decimalsAmplitudeNoiseVpp = 3;

    const double maxAmplitudeNoiseVrms   = 2.09;
    const double minAmplitudeNoiseVrms   = 0.00209;
    const double stepAmplitudeNoiseVrms  = 0.01;
    const int decimalsAmplitudeNoiseVrms = 3;

    const double maxAmplitudeNoisedBm   = +19.41;
    const double minAmplitudeNoisedBm   = -40; // -40.59
    const double stepAmplitudeNoisedBm  = 0.01;
    const int decimalsAmplitudeNoisedBm = 3;

    const double maxAmplitudeArbitraryVpp   = 10;
    const double minAmplitudeArbitraryVpp   = 0.01;
    const double stepAmplitudeArbitraryVpp  = 0.01;
    const int decimalsAmplitudeArbitraryVpp = 3;

    const double maxOffsetV   = 5.00;
    const double minOffsetV   = 0.00;
    const double stepOffsetV  = 0.1;
    const int decimalsOffsetV = 2;

    const double   maxFrequencySine = 30.2E6;
    const double   minFrequencySine = 1E-6;
    const double  stepFrequencySine = 1E-6;
    const int decimalsFrequencySine = 6;

    const double   maxFrequencySquare = 30.2E6;
    const double   minFrequencySquare = 1E-6;
    const double  stepFrequencySquare = 1E-6;
    const int decimalsFrequencySquare = 6;

    const double   maxFrequencyRamp = 10E3;
    const double   minFrequencyRamp = 1E-6;
    const double  stepFrequencyRamp = 1E-6;
    const int decimalsFrequencyRamp = 6;

    const double   maxFrequencyTriangle = 10E3;
    const double   minFrequencyTriangle = 1E-6;
    const double  stepFrequencyTriangle = 1E-6;
    const int decimalsFrequencyTriangle = 6;

    const double   maxFrequencyNoise = 10E6;
    const double   minFrequencyNoise = 10E6;
    const double  stepFrequencyNoise = 0;
    const int decimalsFrequencyNoise = 0;

    const double   maxFrequencyArbitrary = 10E6;
    const double   minFrequencyArbitrary = 10E6;
    const double  stepFrequencyArbitrary = 0;
    const int decimalsFrequencyArbitrary = 0;

    const int minAMDepth = -100;
    const int maxAMDepth = +100;

    const double   maxModulationRate = 10E3;
    const double   minModulationRate = 1E-3;
    const double  stepModulationRate = 1;
    const int decimalsModulationRate = 3;


public:
    explicit DS345();

    //∂ЧТО ЗА ШТУКА И ГДЕ ИСПОЛЬЗУЕТСЯ??- не исползуется, обойдёмся
    //explicit DS345(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0);
    ~DS345();

    void initAmplitudeTypeList();
    double getMinAmplitude(const std::string &waveform, const std::string &unit) const;
    double getMaxAmplitude(const std::string &waveform, const std::string &unit) const;
    double getStepAmplitude(const std::string &waveform, const std::string &unit) const;
    double getDecimalsAmplitude(const std::string &waveform, const std::string &unit) const;
    bool isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &unit) const;

    double getMinFrequency(const std::string &waveform) const;
    double getMaxFrequency(const std::string &waveform) const;
    double getStepFrequency(const std::string &waveform) const;
    double getDecimalsFrequency(const std::string &waveform) const;
    bool isValidFrequency(const double &frequency, const std::string &waveform) const;

    void initFunctionList();

    int getMinAMDepth() const;
    int getMaxAMDepth() const;
    bool isValidAMDepth(const int &persentage) const;
    bool setAMdepth(const int &persentage) const;
    int getAMdepth() const;

    double getMinFMSpan(const std::string &waveform) const;
    double getMaxFMSpan(const std::string &waveform) const;
    bool isValidFMSpan(const int &span, const std::string &waveform) const;
    bool setFMSpan(const double &span) const;
    double getFMSpan() const;

    void initModulationFunctionList();
    std::vector<std::string> getModulationFunctionList() const;
    int modulationFunctionNumberFromString(const std::string &function_string) const;
    std::string modulationFunctionStringFromNumber(const int &function_number) const;
    bool setModulationFunction(const int &function) const;
    bool setModulationFunction(const std::string &function) const;
    std::string getModulationFunction() const;

    bool setModulationEnabled(const bool &enable) const;
    bool getModulationEnabled() const; //bool

    void initModulationTypeList();
    std::vector<std::string> getModulationTypeList() const;
    int modulationTypeNumberFromString(const std::string &type_string) const;
    std::string modulationTypeStringFromNumber(const int &type_number) const;
    bool setModulationType(const int &type) const;
    bool setModulationType(const std::string &type) const;
    std::string getModulationType() const;

    double getMinModulationRate() const;
    double getMaxModulationRate() const;
    double getStepModulationRate() const;
    double getDecimalsModulationRate() const;
    bool isValidModulationRate(const double &rate) const;
    bool setModulationRate(const double &rate) const;
    double getModulationRate() const;

    double getMinModulationSpan(const std::string &waveform) const;
    double getMaxModulationSpan(const std::string &waveform) const;
    double getStepModulationSpan(const std::string &waveform) const;
    double getDecimalsModulationSpan(const std::string &waveform) const;
    bool isValidModulationSpan(const double &span, const std::string &waveform) const;
    bool setModulationSpan(const double &span) const;
    double getModulationSpan() const;

};

#endif // DS345_H
