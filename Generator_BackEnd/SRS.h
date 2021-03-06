#ifndef SRS_H
#define SRS_H

#include "Timer.h"
#include "QtSTLConvertion.h"

#include "SerialPortCommunication.h"

#include <vector>
#include <string>
#include <map>
#include <list>



class SRS : public SerialPortCommunication {
public:
    explicit SRS();
    ~SRS();

    std::vector < std::string > getSupportedList() const;

    int  getAttemptsToConnect(                                  ) const;
    void setAttemptsToConnect(const int &new_attempts_to_connect)      ;

    std::string getIDN  (bool* succeed = nullptr) const;
    std::string getModel(bool* succeed = nullptr) const;

    bool isActive() const;

    std::string detect(const std::string &port_name, bool* succeed = nullptr) const;

    std::map < std::string , std::vector < std::string > > scanAllPorts() const;

//    //вернул кусок с этими 4 ф-циями/ НАДО убрать Qstring - СКАТАТЬ У ЛЁШИ-ВИТИ - тупо перемещаем его на уровень выше в SRSGenetator, отсюда удаляем
//    int numberFromString(const QStringList &list, const QString &string) const;
//    QString stringFromNumber(const QStringList &list, const int &number) const;
//    bool isValidString(const QStringList &list, const QString &string) const;
//    bool isValidNumber(const QStringList &list, const int &number) const;
//    //

protected:
    std::vector < std::string > supported_models = {
                                                    "DS335", "DS345",
                                                    "SR830", "SR844", "SR865", "SR865A",
                                                    "PTC10"
                                                   };

    int attempts_to_connect = 5;

    inline static const std::string command_terminator = "\n";

    inline static const std::string query_suffix = "?";
    inline static const std::string separator    = " ";

    inline static const std::string IDN = "*IDN";

    // этот костыль потом сломается - ∂свинья. Если присмотреться к connect - он уже принимает строку
    std::unordered_map < std::string , QSerialPort::DataBits    > SRS_string_to_data_bits    = {
                                                                                                {"8", QSerialPort::Data8}
                                                                                               };
    std::unordered_map < std::string , QSerialPort::FlowControl > SRS_string_to_flow_control = {
                                                                                                {  "NO", QSerialPort::NoFlowControl  },
                                                                                                {"HARD", QSerialPort::HardwareControl}
                                                                                               };
    std::unordered_map < std::string , QSerialPort::Parity      > SRS_string_to_parity       = {
                                                                                                {   "NO", QSerialPort::NoParity   },
                                                                                                {  "ODD", QSerialPort::OddParity  },
                                                                                                { "EVEN", QSerialPort::EvenParity }
                                                                                               };
    std::unordered_map < std::string , QSerialPort::StopBits    > SRS_string_to_stop_bits    = {
                                                                                                {  "1",  QSerialPort::OneStop       },
                                                                                                {  "2",  QSerialPort::TwoStop       }
                                                                                               };
    //
};

#endif // SRS_H
