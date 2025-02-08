//
// Created by 15428 on 8/2/2025.
//
#include "packet.hpp"

// 发送 Modbus 数据包
void sendPacket(const Packet& pkt) {
    std::cout << "Packet: [ "
              << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(pkt.byte1) << " "
              << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(pkt.byte2) << " "
              << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(pkt.byte3) << " | ";

    for (auto d : pkt.data) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(d) << " ";
    }

    // CRC通常由两个字节组成，这里假设为uint16_t类型
    std::cout << "| CRC: "
              << std::hex << std::setfill('0') << std::setw(4) << pkt.crc
              << " ]\n";
}
