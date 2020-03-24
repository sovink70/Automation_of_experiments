#ifndef SRSGENERATOR_H
#define SRSGENERATOR_H

#include "SRS.h"

class SRSGenerator : public SRS
{
protected:
    SRS* srs;

    std::vector<std::string> baudrateList;
    std::vector<std::string> amplitudeTypeList;
    std::vector<std::string> functionList;
    std::vector<std::string> outputImpedanceList;
    std::vector<std::string> modulationFunctionList;
    std::vector<std::string> modulationTypeList;

    const double maxOffsetV   = 5.00;
    const double minOffsetV   = 0.00;
    const double stepOffsetV  = 0.1;
    const int decimalsOffsetV = 2;

public:
    void initBaudrateList();
    std::vector<std::string> getBaudrateList() const;
    bool isValidBaudrate(const int &baudrate) const;

    void setWriteTimeout(const int &new_writeTimeout);
    int getWriteTimeout() const;

    void setReadTimeout(const int &new_readTimeout);
    int getReadTimeout() const;

    void setReadWaitTimeout(const int &new_readWaitTimeout);
    int getReadWaitTimeout() const;

    int numberFromString(const std::vector< std::string> &vector, const std::string &string) const;
    std::string stringFromNumber(const std::vector< std::string> &vector, const int &number) const;
    bool isValidString(const std::vector< std::string> &vector, const std::string &string) const;
    bool isValidNumber(const std::vector< std::string> &vector, const int &number) const;

    std::vector<std::string> getAmplitudeTypeList() const;
    bool isValidAmplitudeType(const std::string &unit) const;
    bool setAmplitude(const double &amplitude, const std::string &unit) const; //bool &VRMS
    double getAmplitude(const std::string &unit) const;

    double getMinOffset() const;
    double getMaxOffset() const;
    double getStepOffset() const;
    double getDecimalsOffset() const;
    bool isValidOffset(const double &offset) const;
    bool setOffset(const double &offset) const;
    double getOffset() const;

    bool setFrequency(const double &frequency) const;
    double getFrequency() const;

    std::vector<std::string> getFunctionList() const;
    int functionNumberFromString(const std::string &function_string) const;
    std::string functionStringFromNumber(const int &function_number) const;
    bool setFunction(const int &function) const;
    bool setFunction(const std::string &function) const;
    std::string getFunction() const;

    bool setInverse(const bool &inverse) const;
    bool getInverse() const; //    bool getInverse() const;

};

#endif // SRSGENERATOR_H
