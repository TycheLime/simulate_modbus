//
// Created by 15428 on 8/2/2025.
//

#include "modbus.hpp"

// 读取 Holding Register
std::vector<uint8_t> ModbusDevice::readHoldingRegisters(uint16_t startAddress, uint16_t count) {
    std::vector<uint8_t> response;
    if (startAddress + count > holdingRegisterStorage.holdingRegisters.size()) {
        std::cerr << "Error: Out of range\n";
        return response;
    }

    // 插入字节数 (count * 2，因为每个寄存器占 2 字节)
    response.push_back(count * 2);

    // 插入数据
    for (size_t i = 0; i < count; i++) {
        uint16_t value = holdingRegisterStorage.holdingRegisters[startAddress + i];
        response.push_back(value >> 8); // 高字节
        response.push_back(value & 0xFF); // 低字节
    }
    return response;
}

std::vector<uint8_t> ModbusDevice::readCoils(uint16_t startAddress, uint16_t count) {
    if (startAddress + count > coilStorage.coils.size()) {
        std::cerr << "Error: Out of range\n";
        return {};
    }

    std::vector<uint8_t> response;
    response.push_back((count + 7) / 8); // 字节数

    for (uint16_t i = 0; i < count; ++i) {
        if (i % 8 == 0) response.push_back(0);
        response.back() |= (coilStorage.coils[startAddress + i] ? 1 : 0) << (i % 8);
    }
    return response;
}

std::vector<uint8_t> ModbusDevice::readDiscreteInputs(uint16_t startAddress, uint16_t count) {
    if (startAddress + count > inputStorage.inputs.size()) {
        std::cerr << "Error: Out of range\n";
        return {};
    }

    std::vector<uint8_t> response;
    response.push_back((count + 7) / 8);

    for (uint16_t i = 0; i < count; ++i) {
        if (i % 8 == 0) response.push_back(0);
        response.back() |= (inputStorage.inputs[startAddress + i] ? 1 : 0) << (i % 8);
    }
    return response;
}

bool ModbusDevice::writeSingleCoil(uint16_t address, bool value) {
    if (address >= coilStorage.coils.size()) {
        std::cerr << "Error: Address out of range\n";
        return false;
    }
    coilStorage.coils[address] = value;
    return true;
}

bool ModbusDevice::writeSingleRegister(uint16_t address, uint16_t value) {
    if (address >= holdingRegisterStorage.holdingRegisters.size()) {
        std::cerr << "Error: Address out of range\n";
        return false;
    }
    holdingRegisterStorage.holdingRegisters[address] = value;
    return true;
}

bool ModbusDevice::writeMultipleCoils(uint16_t startAddress, const std::vector<bool> &values) {
    if (startAddress + values.size() > coilStorage.coils.size()) {
        std::cerr << "Error: Address out of range\n";
        return false;
    }
    for (size_t i = 0; i < values.size(); ++i) {
        coilStorage.coils[startAddress + i] = values[i];
    }
    return true;
}

bool ModbusDevice::writeMultipleRegisters(uint16_t startAddress, const std::vector<uint16_t> &values) {
    if (startAddress + values.size() > holdingRegisterStorage.holdingRegisters.size()) {
        std::cerr << "Error: Address out of range\n";
        return false;
    }
    for (size_t i = 0; i < values.size(); ++i) {
        holdingRegisterStorage.holdingRegisters[startAddress + i] = values[i];
    }
    return true;
}
