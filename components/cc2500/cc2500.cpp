#include "esphome/core/log.h"
#include "cc2500.h"

#include <cinttypes>

namespace esphome {
namespace cc2500 {

static const char *TAG = "cc2500";

void CC2500Component::setup() {
	ESP_LOGCONFIG(TAG, "Setting up Living Colors gen 1 component...");
	this->spi_setup();

    // reset device (0x30)
	// this->send_strobe_(CC2500_SRES);
    this->reset_();
    this->reset_();

//    // GDO2 Output Pin Configuration
//    // this->write_reg_(REG_IOCFG2, VAL_IOCFG2_DEFAULT);
//    //this->write_reg_(REG_IOCFG2, 0x06);
//
//    // GDO1 Output Pin Configuration
//    //this->write_reg_(REG_IOCFG1, 0x01);
//    this->write_reg_(REG_IOCFG1, VAL_IOCFG1_DEFAULT);
//
//    // GDO0 Output Pin Configuration
//    // this->write_reg_(REG_IOCFG0, 0x06); // 0x06
//
//    // RX FIFO and TX FIFO Thresholds
//    //this->write_reg_(REG_FIFOTHR, 0x0D);
//    this->write_reg_(REG_FIFOTHR, VAL_FIFOTHR_DEFAULT);
//
//    // Packet Length
//    this->write_reg_(REG_PKTLEN, VAL_PKTLEN_DEFAULT); // 0xFF
//
//    // Packet Automation Control
//    this->write_reg_(REG_PKTCTRL1, VAL_PKTCTRL1_DEFAULT);
//    //this->write_reg_(REG_PKTCTRL0, VAL_PKTCTRL0); // 0x05, Data whitening off
//    this->write_reg_(REG_PKTCTRL0, VAL_PKTCTRL0_DEFAULT);

    // Frequency Synthesizer Control
    this->write_reg_(REG_FSCTRL1, VAL_FSCTRL1); // 0x09
    this->write_reg_(REG_FSCTRL0, VAL_FSCTRL0); // 0x00

    // Frequency Control Word
    this->write_reg_(REG_FREQ2, VAL_FREQ2); // 0x5D
    this->write_reg_(REG_FREQ1, VAL_FREQ1); // 0x93
    this->write_reg_(REG_FREQ0, VAL_FREQ0); // 0xB1

    // Modem Configuration
    this->write_reg_(REG_MDMCFG4, VAL_MDMCFG4); // 0x2D
    this->write_reg_(REG_MDMCFG3, VAL_MDMCFG3); // 0x3B
    this->write_reg_(REG_MDMCFG2, VAL_MDMCFG2); // 0x73, Modulation format MSK
    // this->write_reg_(REG_MDMCFG1, VAL_MDMCFG1); // 0xA2
    this->write_reg_(REG_MDMCFG1, VAL_MDMCFG1_DEFAULT);
    this->write_reg_(REG_MDMCFG0, VAL_MDMCFG0_DEFAULT);

//    // Modem Deviation Setting
//    // this->write_reg_(REG_DEVIATN, 0x01);
//    //this->write_reg_(REG_DEVIATN, 0x00);
//    this->write_reg_(REG_DEVIATN, VAL_DEVIATN_DEFAULT);
//
//    // this->write_reg_(REG_MCSM2, 0x07); // 0x07
//    // this->write_reg_(REG_MCSM1, 0x30); // 0x30
//
    // Main Radio Control State Machine
    //this->write_reg_(REG_MCSM0, VAL_MCSM0); // 0x18
    //this->write_reg_(REG_MCSM0, VAL_MCSM0_DEFAULT);
    this->write_reg_(REG_MCSM0, 0b00010100); // Automatically calibrate when going from IDLE to RX or TX (or FSTXON)

//    // Frequency Offset Compensation
//    //this->write_reg_(REG_FOCCFG, VAL_FOCCFG); // 0x1D
//    this->write_reg_(REG_FOCCFG, VAL_FOCCFG_DEFAULT);
//
//    // Bit Synchronization Configuration
//    //this->write_reg_(REG_BSCFG, VAL_BSCFG); // 0x1C
//    this->write_reg_(REG_BSCFG, VAL_BSCFG_DEFAULT);
//
//    // AGC Control
//    // this->write_reg_(REG_AGCCTRL2, VAL_AGCCTRL2); // 0xC7
//    //this->write_reg_(REG_AGCCTRL2, 0x07);
//    this->write_reg_(REG_AGCCTRL2, VAL_AGCCTRL2_DEFAULT);
//    //this->write_reg_(REG_AGCCTRL1, VAL_AGCCTRL1); // 0x00
//    this->write_reg_(REG_AGCCTRL1, VAL_AGCCTRL1_DEFAULT);
//    //this->write_reg_(REG_AGCCTRL0, VAL_AGCCTRL0); // 0xB2
//    this->write_reg_(REG_AGCCTRL0, VAL_AGCCTRL0_DEFAULT);
//
//    // this->write_reg_(REG_WOREVT1, 0x87);
//    // this->write_reg_(REG_WOREVT0, 0x6B);
//    // this->write_reg_(REG_WORCTRL, 0xF8);
//
//    // Front End RX Configuration
//    //this->write_reg_(REG_FREND1, 0xB6); // 0xB6
//    this->write_reg_(REG_FREND1, VAL_FREND1_DEFAULT); // 0x56, Reset
//
//    // Front End TX configuration
//    //this->write_reg_(REG_FREND0, 0x10); // 0x10
//    this->write_reg_(REG_FREND0, VAL_FREND0_DEFAULT); // 0x08, Reset
//
//    // Frequency Synthesizer Calibration
//    //this->write_reg_(REG_FSCAL3, 0xEA); // 0xEA
//    this->write_reg_(REG_FSCAL3, VAL_FSCAL3_DEFAULT); // 0xA9, Reset
//    this->write_reg_(REG_FSCAL2, VAL_FSCAL2_DEFAULT); // 0x0A, Reset
//    //this->write_reg_(REG_FSCAL1,  0x00); // 0x00
//    this->write_reg_(REG_FSCAL1, VAL_FSCAL1_DEFAULT); // 0x20, Reset
//    //this->write_reg_(REG_FSCAL0,  0x11); // 0x11
//    this->write_reg_(REG_FSCAL0, VAL_FSCAL0_DEFAULT); // 0x11
//
//    // RC Oscillator Configuration
//	this->write_reg_(REG_RCCTRL1, VAL_RCCTRL1_DEFAULT); // 0x41, Reset
//	this->write_reg_(REG_RCCTRL0, VAL_RCCTRL0_DEFAULT); // 0x00, Reset
//
//    // Frequency Synthesizer Calibration Control
//	//this->write_reg_(REG_FSTEST, VAL_FSTEST_DEFAULT); // 0x59, Reset. For test only. Do not write to this register.
//
//    // Various Test Settings
//    this->write_reg_(REG_TEST2, VAL_TEST2_DEFAULT); // 0x88, Reset
//    this->write_reg_(REG_TEST1, VAL_TEST1_DEFAULT); // 0x31, Reset
//    this->write_reg_(REG_TEST0, VAL_TEST0_DEFAULT); // 0x0B, Reset

    // Output Power Programming
    // this->write_reg_(REG_PATABLE, 0xFF);
    this->write_reg_(REG_PATABLE, this->output_power_.value_or(0xFF));

	// SIDLE
	this->send_strobe_(CC2500_SIDLE);

	// SPWD - enter power down mode when CSn goes high
	this->send_strobe_(CC2500_SPWD);

	// SIDLE
	this->send_strobe_(CC2500_SIDLE);
}

void CC2500Component::dump_config() {
	ESP_LOGCONFIG(TAG, "CC2500 component:");
	LOG_PIN("  CS PIN: ", this->cs_);
	if (this->output_power_.has_value())
		ESP_LOGCONFIG(TAG, "  Output power: %d", this->output_power_.value());
//	if (this->sniff_after_x_commands_.has_value())
//		ESP_LOGCONFIG(TAG, "  Sniff after X commands sent: %d", this->sniff_after_x_commands_.value());
}

//void CC2500Component::loop() {
////	// Sniffing slows down command sending. Therefore we only sniff if we are
////	// not sending commands
////	if(!this->busy_) {
////		this->busy_ = true;
////		this->sniff_();
////		this->busy_ = false;
////	}
//
//	//	if (this->command_queue_.empty()) {
////		this->sniff_();
////	} else if (this->commands_sent_
////			% this->sniff_after_x_commands_.value_or(5) == 0) {
////		this->sniff_();
////	}
//
////	if(!this->command_queue_.empty()) {
////		delayMicroseconds(500);
////		ESP_LOGV(TAG, "command queue size: %d", this->command_queue_.size());
////		Command command = this->command_queue_.front();
////		delayMicroseconds(500);
////		this->send_command(command.data, command.length);
////		delayMicroseconds(500);
////		this->command_queue_.pop_front();
////		delayMicroseconds(500);
////	}
//	delayMicroseconds(10);
//}

void CC2500Component::reset_() {
	this->enable();
	delayMicroseconds(2);
	this->write_byte(CC2500_SRES);
	delayMicroseconds(45);
	this->disable();
}

uint8_t CC2500Component::write_reg_(uint8_t address, uint8_t value) {
	this->enable();
	this->write_byte(address);
	uint8_t result = this->transfer_byte(value);
	this->disable();
	return result;
}

void CC2500Component::write_reg_(uint8_t address, uint8_t *data, uint8_t length) {
//	ESP_LOGV(TAG, "write_reg_(0x%02X, 0x%030X, %d)", address, data, length);
	this->enable();
	this->write_byte(address);
	// Send data
	this->transfer_array(data, length);
	this->disable();
}

//uint8_t CC2500::read_reg_(uint8_t address) {
//	address += 0x80;
//	this->enable();
//	uint8_t value = this->transfer_byte(address);
//	this->disable();
//	return value;
//}

void CC2500Component::send_strobe_(uint8_t strobe) {
	this->enable();
	this->write_byte(strobe);
	this->disable();
}

//void CC2500::queue_command(Command command) {
//	ESP_LOGV(TAG, "queue_command");
//	ESP_LOGV(TAG, "  channel: %d", command.channel);
//	ESP_LOGV(TAG, "  modulation: 0x%030X", (uint8_t) command.modulation);
//	ESP_LOGV(TAG, "  manchester encoding: %s", command.manchester_encoding ? "enabled" : "disabled");
//	ESP_LOGV(TAG, "  data: 0x%032"  PRIX64, command.data);
//	ESP_LOGV(TAG, "  length: %d", command.length);
//	auto pair = std::make_pair(address, Command { .data = data,
//			.length = length });
//	this->command_queue_.push_back(command);
//}

void CC2500Component::send_command(Command command) {
	while(this->busy_) {
		ESP_LOGV(TAG, "busy");
		delayMicroseconds(1);
	}

	this->busy_ = true;

	ESP_LOGV(TAG, "send_command");
	ESP_LOGV(TAG, "  channel: %d", command.channel);
//	ESP_LOGV(TAG, "  modulation: 0x%X", (uint8_t) command.modulation);
//	ESP_LOGV(TAG, "  manchester encoding: %s", command.manchester_encoding ? "enabled" : "disabled");
	ESP_LOGV(TAG, "  data: 0x%032"  PRIX64, command.data);
	ESP_LOGV(TAG, "  length: %d", command.length);

	this->write_reg_(REG_ADDR, command.device_address);
	this->write_reg_(REG_CHANNR, command.channel);

	this->send_strobe_(CC2500_SIDLE);
	this->write_reg_(0x7F, command.data, command.length);
	this->send_strobe_(CC2500_STX);

	this->commands_sent_++;
	this->busy_ = false;
}

//void CC2500Component::sniff_() {
//	std::vector < uint8_t > packet;
//
//	this->send_strobe_(CC2500_SRX);
//	this->write_reg_(REG_IOCFG1, 0x01);
//	delay(20);
//
//	uint8_t len = this->read_reg_(REG_FIFO);
//	if (len > 15) {
//		for (int i = 0; i < len; i++) {
//			packet.push_back(this->read_reg_(REG_FIFO));
//		}
//
//		ESP_LOGV(TAG, "Sniffed packet: 0x%032" PRIX64, packet);
//		//this->on_remote_click_callback_.call(packet);
//	}
//	this->send_strobe_(CC2500_SIDLE);
//	this->send_strobe_(CC2500_SFRX);
//}

void CC2500Client::set_cc2500_parent(CC2500Component *parent) {
	this->parent_ = parent;
	this->parent_->add_device(this);
}

void CC2500Client::send_command(uint8_t *data, uint8_t length) {
	cc2500::Command command = cc2500::Command();
	command.device_address = this->device_address_;
	command.channel = this->channel_;
	command.length = length;
	command.data = data;

	this->parent_->send_command(command);
}

}
}
