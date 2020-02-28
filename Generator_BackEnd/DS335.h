#ifndef DS335_H
#define DS335_H

#include "SRSgenerator.h"

class DS335 : public SRSGenerator
{

private:
    const double maxAmplitude50OhmsSineVpp   = 10;
    const double minAmplitude50OhmsSineVpp   = 0.05;
    const double stepAmplitude50OhmsSineVpp  = 0.01;
    const int decimalsAmplitude50OhmsSineVpp = 3;

    const double maxAmplitude50OhmsSineVrms   = 3.54;
    const double minAmplitude50OhmsSineVrms   = 0.02;
    const double stepAmplitude50OhmsSineVrms  = 0.01;
    const int decimalsAmplitude50OhmsSineVrms = 3;

    const double maxAmplitudeHighZSineVpp   = 20;
    const double minAmplitudeHighZSineVpp   = 0.1;
    const double stepAmplitudeHighZSineVpp  = 0.01;
    const int decimalsAmplitudeHighZSineVpp = 3;

    const double maxAmplitudeHighZSineVrms   = 7.07;
    const double minAmplitudeHighZSineVrms   = 0.04;
    const double stepAmplitudeHighZSineVrms  = 0.01;
    const int decimalsAmplitudeHighZSineVrms = 3;

    const double maxAmplitude50OhmsSquareVpp   = 10;
    const double minAmplitude50OhmsSquareVpp   = 0.05;
    const double stepAmplitude50OhmsSquareVpp  = 0.01;
    const int decimalsAmplitude50OhmsSquareVpp = 3;

    const double maxAmplitude50OhmsSquareVrms   = 5;
    const double minAmplitude50OhmsSquareVrms   = 0.03;
    const double stepAmplitude50OhmsSquareVrms  = 0.01;
    const int decimalsAmplitude50OhmsSquareVrms = 3;

    const double maxAmplitudeHighZSquareVpp   = 20;
    const double minAmplitudeHighZSquareVpp   = 0.1;
    const double stepAmplitudeHighZSquareVpp  = 0.01;
    const int decimalsAmplitudeHighZSquareVpp = 3;

    const double maxAmplitudeHighZSquareVrms   = 10;
    const double minAmplitudeHighZSquareVrms   = 0.05;
    const double stepAmplitudeHighZSquareVrms  = 0.01;
    const int decimalsAmplitudeHighZSquareVrms = 3;

    const double maxAmplitude50OhmsTriangleVpp   = 10;
    const double minAmplitude50OhmsTriangleVpp   = 0.05;
    const double stepAmplitude50OhmsTriangleVpp  = 0.01;
    const int decimalsAmplitude50OhmsTriangleVpp = 3;

    const double maxAmplitude50OhmsTriangleVrms   = 2.89;
    const double minAmplitude50OhmsTriangleVrms   = 0.01;
    const double stepAmplitude50OhmsTriangleVrms  = 0.01;
    const int decimalsAmplitude50OhmsTriangleVrms = 3;

    const double maxAmplitudeHighZTriangleVpp   = 20;
    const double minAmplitudeHighZTriangleVpp   = 0.1;
    const double stepAmplitudeHighZTriangleVpp  = 0.01;
    const int decimalsAmplitudeHighZTriangleVpp = 3;

    const double maxAmplitudeHighZTriangleVrms   = 5.77;
    const double minAmplitudeHighZTriangleVrms   = 0.03;
    const double stepAmplitudeHighZTriangleVrms  = 0.01;
    const int decimalsAmplitudeHighZTriangleVrms = 3;

    const double maxAmplitude50OhmsRampVpp   = 10;
    const double minAmplitude50OhmsRampVpp   = 0.05;
    const double stepAmplitude50OhmsRampVpp  = 0.01;
    const int decimalsAmplitude50OhmsRampVpp = 3;

    const double maxAmplitude50OhmsRampVrms   = 2.89;
    const double minAmplitude50OhmsRampVrms   = 0.01;
    const double stepAmplitude50OhmsRampVrms  = 0.01;
    const int decimalsAmplitude50OhmsRampVrms = 3;

    const double maxAmplitudeHighZRampVpp   = 20;
    const double minAmplitudeHighZRampVpp   = 0.1;
    const double stepAmplitudeHighZRampVpp  = 0.01;
    const int decimalsAmplitudeHighZRampVpp = 3;

    const double maxAmplitudeHighZRampVrms   = 5.77;
    const double minAmplitudeHighZRampVrms   = 0.03;
    const double stepAmplitudeHighZRampVrms  = 0.01;
    const int decimalsAmplitudeHighZRampVrms = 3;

    const double maxAmplitude50OhmsNoiseVpp   = 10;
    const double minAmplitude50OhmsNoiseVpp   = 0.05;
    const double stepAmplitude50OhmsNoiseVpp  = 0.1;
    const int decimalsAmplitude50OhmsNoiseVpp = 3;

    const double maxAmplitude50OhmsNoiseVrms   = 1.62;
    const double minAmplitude50OhmsNoiseVrms   = 0.01;
    const double stepAmplitude50OhmsNoiseVrms  = 0.01;
    const int decimalsAmplitude50OhmsNoiseVrms = 3;

    const double maxAmplitudeHighZNoiseVpp   = 20;
    const double minAmplitudeHighZNoiseVpp   = 0.1;
    const double stepAmplitudeHighZNoiseVpp  = 0.01;
    const int decimalsAmplitudeHighZNoiseVpp = 3;

    const double maxAmplitudeHighZNoiseVrms   = 3.24;
    const double minAmplitudeHighZNoiseVrms   = 0.02;
    const double stepAmplitudeHighZNoiseVrms  = 0.01;
    const int decimalsAmplitudeHighZNoiseVrms = 3;

    const double maxOffsetV   = 5.00;
    const double minOffsetV   = 0.00;
    const double stepOffsetV  = 0.1;
    const int decimalsOffsetV = 2;

    const double   maxFrequencySine = 3.1E6;
    const double   minFrequencySine = 1E-6;
    const double  stepFrequencySine = 1E-6;
    const int decimalsFrequencySine = 6;

    const double   maxFrequencySquare = 3.1E6;
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

    const double   maxFrequencyNoise = 3.5E6;
    const double   minFrequencyNoise = 3.5E6;
    const double  stepFrequencyNoise = 0;
    const int decimalsFrequencyNoise = 0;


public:
    explicit DS335();
    ~DS335();

    void initAmplitudeTypeList();
    double getMinAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getMaxAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getStepAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getDecimalsAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    bool isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &outputZ, const std::string &unit) const;

    double getMinFrequency(const std::string &waveform) const;
    double getMaxFrequency(const std::string &waveform) const;
    double getStepFrequency(const std::string &waveform) const;
    double getDecimalsFrequency(const std::string &waveform) const;
    bool isValidFrequency(const double &frequency, const std::string &waveform) const;

    void initFunctionList();

    bool setSynchronization(const bool &synchronization) const;
    bool getSynchronization() const;

    void initOutputImpedanceList();
    std::vector<std::string> getOutputImpedanceList() const;
    int outputImpedanceNumberFromString(const std::string &outputImpedance_string) const;
    std::string outputImpedanceStringFromNumber(const int &outputImpedance_number) const;
    bool setOutputImpedance(const int &outputImpedance) const;
    bool setOutputImpedance(const std::string &outputImpedance) const;
    std::string getOutputImpedance() const;

};

#endif // DS335_H
