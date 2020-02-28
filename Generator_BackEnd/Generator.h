#ifndef GENERATOR_H
#define GENERATOR_H

#include "SRS.h"
#include "DS335.h"
#include "DS345.h"

//нужно, чтобы запоминать в принципе состояние генератора
struct Generator_State
{
    std::string model;
    double amplitude;// In Vrms
    double offset;
    double frequency;
    std::string function;
    bool inverse;
    bool synchronization;
    std::string outputImpedance;
    int amDepth;
    double fmSpan;
    std::string modulationFunction;
    bool modulationEnabled;
    std::string modulationType;
    double modulationRate;
    double modulationSpan;
};

class Generator //: public QObject
{

private:
    SRS* srs;

    DS335* ds335;
    DS345* ds345;

    std::string generatorModel;

    const double Err = 1E-10;

    const int waitTime = 700;

public:
    explicit Generator();
    explicit Generator(const std::string &new_generatorModel);
    explicit Generator(const std::string &portName, const std::string &baudrate, const std::string &dataBit, const std::string &stopBit, const std::string &parity, const std::string &flowcontrol, const std::string &new_generatorModel = "");     //explicit Generator(const std::string &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0, const std::string &new_generatorModel = "");
    //explicit Generator(const std::string &portName);
    explicit Generator(DS335* new_ds335);
    explicit Generator(DS345* new_ds345);
    ~Generator();

    void toNULL();
    void init();

    Generator_State getState();
    bool setState(const Generator_State &state);

    void wait(const double &x = 1) const;

    void setDS335(DS335* new_ds335);
    DS335* getDS335() const;
    void setDS345(DS345* new_ds345);
    DS345* getDS345() const;

    //bool openSerial(QSerialPort *serial) const; - уже есть такое в SerialPortCommunicationQt

    std::vector<std::string> getSupportedModels() const;
    void setGeneratorModel(const std::string &new_generatorModel);
    std::string getGeneratorModel() const;
//    bool autoSetGeneratorModel(QSerialPort *serial);
//    bool autoSetGeneratorModel(const QString &portName, const int &baudrate);
//    bool autoSetGeneratorModel(const QString &portName);

//    bool setConnection(const QString &portName, const int &baudrate, const int &stopBit = 1, const int &parity = 0, const QString &new_generatorModel = "");
//    bool setConnectionBrute(const QString &portName, const QString &new_generatorModel = "");

    //стырил у Вити (внешность и идею, что их 4 штуки) + Гоши (внутренние кишки). Мб не все пригодятся, SET добавил сам, чтобы не переопределить тот connect, который сидит в SerialPortCommunicationQt
    bool SETconnect(const std::string &new_port_name   ,
                 const std::string &new_baudrate    ,
                 const std::string &new_data_bits   ,
                 const std::string &new_stop_bits   ,
                 const std::string &new_parity      ,
                 const std::string &new_flow_control,
                 const std::string &new_model);
    bool SETconnect(const std::string &new_port_name   ,
                 const std::string &new_baudrate    ,
                 const std::string &new_data_bits   ,
                 const std::string &new_stop_bits   ,
                 const std::string &new_parity      ,
                 const std::string &new_flow_control);
    bool SETconnect(const std::string &new_port_name   ,
                 const std::string &new_baudrate    );
    bool SETconnect(const std::string &new_port_name   );

    bool disconnect() const;


    std::vector<std::string> getBaudrateList() const;
    bool isValidBaudrateAll(const int &baudrate) const;
    bool isValidBaudrate(const int &baudrate) const;
    bool changeBaudrate(const int &baudrate);

    void setWriteTimeout(const int &new_writeTimeout);
    int getWriteTimeout() const;

    void setReadTimeout(const int &new_readTimeout);
    int getReadTimeout() const;

    void setReadWaitTimeout(const int &new_readWaitTimeout);
    int getReadWaitTimeout() const;

    void setAttemptsToConnect(const int &new_attemptsToConnect);
    int getAttemptsToConnect() const;

    bool isActive() const;

    bool send(const std::string &command, std::string &response, const bool &wait_for_response) const;
    bool sendCommand(const std::string &command) const;
    bool sendQuery(const std::string &command, std::string &response) const;
    std::string ask(const std::string &command) const;

    std::string getIDN(bool* succeed) const;

    //bool test() const;

    bool setDefaultSettings() const;

    double getAverageInputTime() const;
    double getAverageOutputTime() const;

    bool workWithAmplitude() const;
    double getDefaultAmplitude() const;
    bool setDefaultAmplitude() const;
    std::vector<std::string> getAmplitudeTypeList() const;
    double getMinAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getMinAmplitude(const std::string &waveform, const std::string &unit) const;
    double getMinAmplitudeCurrent(const std::string &unit) const;
    double getMaxAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getMaxAmplitude(const std::string &waveform, const std::string &unit) const;
    double getMaxAmplitudeCurrent(const std::string &unit) const;
    double getStepAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getStepAmplitude(const std::string &waveform, const std::string &unit) const;
    double getStepAmplitudeCurrent(const std::string &unit) const;
    double getDecimalsAmplitude(const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    double getDecimalsAmplitude(const std::string &waveform, const std::string &unit) const;
    double getDecimalsAmplitudeCurrent(const std::string &unit) const;
    bool isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &outputZ, const std::string &unit) const;
    bool isValidAmplitude(const double &amplitude, const std::string &waveform, const std::string &unit) const;
    bool isValidAmplitude(const double &amplitude, const std::string &unit) const; //
    bool isValidAmplitudeType(const std::string &unit) const;
    bool setAmplitude(const double &amplitude, const std::string &unit) const;
    double getAmplitude(const std::string &unit) const;

    bool workWithOffset() const;
    double getDefaultOffset() const;
    bool setDefaultOffset() const;
    double getMinOffset() const;
    double getMaxOffset() const;
    double getStepOffset() const;
    double getDecimalsOffset() const;
    bool isValidOffset(const double &offset) const;
    bool setOffset(const double &offset) const;
    double getOffset() const;

    bool workWithFrequency() const;
    double getDefaultFrequency() const;
    bool setDefaultFrequency() const;
    double getMinFrequency(const std::string &waveform) const;
    double getMinFrequencyCurrent() const;
    double getMaxFrequency(const std::string &waveform) const;
    double getMaxFrequencyCurrent() const;
    double getStepFrequency(const std::string &waveform) const;
    double getStepFrequencyCurrent() const;
    double getDecimalsFrequency(const std::string &waveform) const;
    double getDecimalsFrequencyCurrent() const;
    //bool isValidFrequency(const double &frequency, const std::string &waveform = "") const;
    bool isValidFrequency(const double &frequency) const; //
    bool setFrequency(const double &frequency) const;
    double getFrequency() const;

    bool workWithFunction() const;
    std::string getDefaultFunction() const;
    bool setDefaultFunction() const;
    std::vector<std::string> getFunctionList() const;
    int functionNumberFromString(const std::string &function_string) const;
    std::string functionStringFromNumber(const int &function_number) const;
    bool setFunction(const int &function) const;
    bool setFunction(const std::string &function) const;
    std::string getFunction() const;

    bool workWithInverse() const;
    bool getDefaultInverse() const;
    bool setDefaultInverse() const;
    bool setInverse(const bool &inverse) const;
    bool getInverse() const;

    bool workWithSynchronization() const;
    bool getDefaultSynchronization() const;
    bool setDefaultSynchronization() const;
    bool setSynchronization(const bool &synchronization) const;
    bool getSynchronization() const;

    bool workWithOutputImpedance() const;
    std::string getDefaultOutputImpedance() const;
    bool setDefaultOutputImpedance() const;
    std::vector<std::string> getOutputImpedanceList() const;
    int outputImpedanceNumberFromString(const std::string &outputImpedance_string) const;
    std::string outputImpedanceStringFromNumber(const int &outputImpedance_number) const;
    bool setOutputImpedance(const int &outputImpedance) const;
    bool setOutputImpedance(const std::string &outputImpedance) const;
    std::string getOutputImpedance() const;

    bool workWithAMDepth() const;
    int getDefaultAMDepth() const;
    bool setDefaultAMDepth() const;
    int getMinAMDepth() const;
    int getMaxAMDepth() const;
    bool isValidAMDepth(const int &persentage) const;
    bool setAMDepth(const int &persentage) const;
    int getAMDepth() const;

    bool workWithFMSpan() const;
    double getDefaultFMSpan() const;
    bool setDefaultFMSpan() const;
    double getMinFMSpan(const std::string &waveform) const;
    double getMinFMSpanCurrent() const;
    double getMaxFMSpan(const std::string &waveform) const;
    double getMaxFMSpanCurrent() const;
    bool isValidFMSpan(const int &span, const std::string &waveform) const;
    bool isValidFMSpan(const int &span) const; //
    bool setFMSpan(const double &span) const;
    double getFMSpan() const;

    bool workWithModulationFunction() const;
    std::string getDefaultModulationFunction() const;
    bool setDefaultModulationFunction() const;
    std::vector<std::string> getModulationFunctionList() const;
    int modulationFunctionNumberFromString(const std::string &function_string) const;
    std::string modulationFunctionStringFromNumber(const int &function_number) const;
    bool setModulationFunction(const int &function) const;
    bool setModulationFunction(const std::string &function) const;
    std::string getModulationFunction() const;

    bool workWithModulationEnabled() const;
    bool getDefaultModulationEnabled() const;
    bool setDefaultModulationEnabled() const;
    bool setModulationEnabled(const bool &enable) const;
    bool getModulationEnabled() const;

    bool workWithModulationType() const;
    std::string getDefaultModulationType() const;
    bool setDefaultModulationType() const;
    std::vector<std::string> getModulationTypeList() const;
    int modulationTypeNumberFromString(const std::string &type_string) const;
    std::string modulationTypeStringFromNumber(const int &type_number) const;
    bool setModulationType(const int &type) const;
    bool setModulationType(const std::string &type) const;
    std::string getModulationType() const;

    bool workWithModulationRate() const;
    double getDefaultModulationRate() const;
    bool setDefaultModulationRate() const;
    double getMinModulationRate() const;
    double getMaxModulationRate() const;
    double getStepModulationRate() const;
    double getDecimalsModulationRate() const;
    bool isValidModulationRate(const double &rate) const;
    bool setModulationRate(const double &rate) const;
    double getModulationRate() const;

    bool workWithModulationSpan() const;
    double getDefaultModulationSpan() const;
    bool setDefaultModulationSpan() const;
    double getMinModulationSpan(const std::string &waveform) const;
    double getMinModulationSpanCurrent() const;
    double getMaxModulationSpan(const std::string &waveform) const;
    double getMaxModulationSpanCurrent() const;
    double getStepModulationSpan(const std::string &waveform) const;
    double getStepModulationSpanCurrent() const;
    double getDecimalsModulationSpan(const std::string &waveform) const;
    double getDecimalsModulationSpanCurrent() const;
    bool isValidModulationSpan(const double &span, const std::string &waveform) const;
    bool isValidModulationSpan(const double &span) const;
    bool setModulationSpan(const double &span) const;
    double getModulationSpan() const;
};

#endif // GENERATOR_H
