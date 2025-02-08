#include <iostream>
#include "modbus.hpp"
#include "packet.hpp"

int main() {
    ModbusDevice device(100, 100, 100, 100);

    // 写入数据
    device.writeSingleCoil(1, true);
    device.writeSingleRegister(2, 1234);

    // 读取数据
    auto coils = device.readCoils(0, 5);
    Packet pkt1 = {1, 1, static_cast<uint8_t>(coils.size()), coils, 0}; // 示例CRC值
    sendPacket(pkt1);

    auto registers = device.readHoldingRegisters(0, 5);
    Packet pkt2 = {1, 3, static_cast<uint8_t>(registers.size()), registers, 0}; // 示例CRC值
    sendPacket(pkt2);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
