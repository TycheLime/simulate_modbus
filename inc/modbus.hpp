//
// Created by 15428 on 8/2/2025.
//

#ifndef MODBUS_MODBUS_HPP
#define MODBUS_MODBUS_HPP

#include <iostream>
#include <vector>

// 定义线圈和寄存器的存储区
struct CoilStorage {
    // 线圈通常表示为布尔值，用于存储开/关状态
    std::vector<bool> coils;
};

struct DiscreteInputStorage {
    std::vector<bool> inputs; // 离散输入 (0x1001 - 0x17D0)
};

struct HoldingRegisterStorage{
    // 保持寄存器通常存储16位的数值，这里使用uint16_t来表示
    std::vector<uint16_t> holdingRegisters;
};

struct InputRegisterStorage {
    std::vector<uint16_t> inputRegisters; // 输入寄存器 (0x3001 - 0x37D0)
};

// 标准Modbus，5位
// 1 ~ 9999
class ModbusDevice{
private:
    CoilStorage coilStorage;
    DiscreteInputStorage inputStorage;
    HoldingRegisterStorage holdingRegisterStorage;
    InputRegisterStorage inputRegisterStorage;


public:
    ModbusDevice(size_t coilCount, size_t inputCount, size_t holdingRegisterCount, size_t inputRegisterCount)
            : coilStorage{std::vector<bool>(coilCount, false)},
              inputStorage{std::vector<bool>(inputCount, false)},
              holdingRegisterStorage{std::vector<uint16_t>(holdingRegisterCount, 0)},
              inputRegisterStorage{std::vector<uint16_t>(inputRegisterCount, 0)} {
    }


    // 功能码 01: 读取输出线圈
    std::vector<uint8_t> readCoils(uint16_t startAddress, uint16_t count);

    // 功能码 02: 读取输入线圈
    std::vector<uint8_t> readDiscreteInputs(uint16_t startAddress, uint16_t count);

    // 功能码 03: 读取输出寄存器
    std::vector<uint8_t> readHoldingRegisters(uint16_t startAddress, uint16_t count);

    // 功能码 05: 写单个输出线圈
    bool writeSingleCoil(uint16_t address, bool value);

    // 功能码 06: 写单个输出寄存器
    bool writeSingleRegister(uint16_t address, uint16_t value);

    // 功能码 15: 写多个输出线圈
    bool writeMultipleCoils(uint16_t startAddress, const std::vector<bool>& values);

    // 功能码 16: 写多个输出寄存器
    bool writeMultipleRegisters(uint16_t startAddress, const std::vector<uint16_t>& values);
};

#endif //MODBUS_MODBUS_HPP
