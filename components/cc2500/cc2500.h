#pragma once

#include <vector>
#include <list>

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace cc2500 {
// Command Strobes
static const uint8_t CC2500_SRES    = 0x30; // Reset chip
static const uint8_t CC2500_SFSTXON = 0x31;
static const uint8_t CC2500_SXOFF   = 0x32; // Turn off crystal oscillator.
static const uint8_t CC2500_SCAL    = 0x33; // Calibrate frequency synthesizer and turn it off
static const uint8_t CC2500_SRX     = 0x34; // Enable RX
static const uint8_t CC2500_STX     = 0x35; // Enable TX
static const uint8_t CC2500_SIDLE   = 0x36; // Exit RX / TX, turn off frequency synthesizer
static const uint8_t CC2500_SWOR    = 0x38; // Start automatic RX polling sequence
static const uint8_t CC2500_SPWD    = 0x39; // Enter power down mode
static const uint8_t CC2500_SFRX    = 0x3A; // Flush the RX FIFO buffer
static const uint8_t CC2500_SFTX    = 0x3B; // Flush the TX FIFO buffer
static const uint8_t CC2500_SWORRST = 0x3C; // Reset real time clock
static const uint8_t CC2500_SNOP    = 0x3D; // No operation

// Configuration Registers
static const uint8_t REG_IOCFG2     = 0x00; // GDO2 output pin configuration
static const uint8_t REG_IOCFG1     = 0x01; // GDO1 output pin configuration
static const uint8_t REG_IOCFG0     = 0x02; // GDO0 output pin configuration
static const uint8_t REG_FIFOTHR    = 0x03; // RX FIFO and TX FIFO thresholds
static const uint8_t REG_SYNC1      = 0x04; // Sync word, high byte
static const uint8_t REG_SYNC0      = 0x05; // Sync word, low byte
static const uint8_t REG_PKTLEN     = 0x06; // Packet length
static const uint8_t REG_PKTCTRL1   = 0x07; // Packet automation control
static const uint8_t REG_PKTCTRL0   = 0x08; // Packet automation control
static const uint8_t REG_ADDR       = 0x09; // Device address
static const uint8_t REG_CHANNR     = 0x0A; // Channel number
static const uint8_t REG_FSCTRL1    = 0x0B; // Frequency synthesizer control
static const uint8_t REG_FSCTRL0    = 0x0C; // Frequency synthesizer control
static const uint8_t REG_FREQ2      = 0x0D; // Frequency control word, high byte
static const uint8_t REG_FREQ1      = 0x0E; // Frequency control word, middle byte
static const uint8_t REG_FREQ0      = 0x0F; // Frequency control word, low byte
static const uint8_t REG_MDMCFG4    = 0x10; // Modem configuration
static const uint8_t REG_MDMCFG3    = 0x11; // Modem configuration
static const uint8_t REG_MDMCFG2    = 0x12; // Modem configuration
static const uint8_t REG_MDMCFG1    = 0x13; // Modem configuration
static const uint8_t REG_MDMCFG0    = 0x14; // Modem configuration
static const uint8_t REG_DEVIATN    = 0x15; // Modem deviation setting
static const uint8_t REG_MCSM2      = 0x16; // Main Radio Control State Machine configuration
static const uint8_t REG_MCSM1      = 0x17; // Main Radio Control State Machine configuration
static const uint8_t REG_MCSM0      = 0x18; // Main Radio Control State Machine configuration
static const uint8_t REG_FOCCFG     = 0x19; // Frequency Offset Compensation configuration
static const uint8_t REG_BSCFG      = 0x1A; // Bit Synchronization configuration
static const uint8_t REG_AGCCTRL2   = 0x1B; // AGC Control
static const uint8_t REG_AGCCTRL1   = 0x1C; // AGC Control
static const uint8_t REG_AGCCTRL0   = 0x1D; // AGC Control
static const uint8_t REG_WOREVT1    = 0x1E; // High byte Event 0 timeout
static const uint8_t REG_WOREVT0    = 0x1F; // Low byte Event 0 timeout
static const uint8_t REG_WORCTRL    = 0x20; // Wake On Radio control
static const uint8_t REG_FREND1     = 0x21; // Front end RX configuration
static const uint8_t REG_FREND0     = 0x22; // Front end TX configuration
static const uint8_t REG_FSCAL3     = 0x23; // Frequency synthesizer calibration
static const uint8_t REG_FSCAL2     = 0x24; // Frequency synthesizer calibration
static const uint8_t REG_FSCAL1     = 0x25; // Frequency synthesizer calibration
static const uint8_t REG_FSCAL0     = 0x26; // Frequency synthesizer calibration
static const uint8_t REG_RCCTRL1    = 0x27; // RC oscillator configuration
static const uint8_t REG_RCCTRL0    = 0x28; // RC oscillator configuration
static const uint8_t REG_FSTEST     = 0x29; // Frequency synthesizer calibration control
static const uint8_t REG_PTEST      = 0x2A; // Production test
static const uint8_t REG_AGCTEST    = 0x2B; // AGC test
static const uint8_t REG_TEST2      = 0x2C; // Various test settings
static const uint8_t REG_TEST1      = 0x2D; // Various test settings
static const uint8_t REG_TEST0      = 0x2E; // Various test settings
//static const uint8_t REG_ = 0x2F;

// Status Registers
static const uint8_t REG_PARTNUM    = 0x30; // CC2500 part number
static const uint8_t REG_VERSION    = 0x31; // Current version number
static const uint8_t REG_FREQEST    = 0x32; // Frequency offset estimate
static const uint8_t REG_LQI        = 0x33; // Demodulator estimate for Link Quality
static const uint8_t REG_RSSI       = 0x34; // Received signal strength indication
static const uint8_t REG_MARCSTATE  = 0x35; // Control state machine state
static const uint8_t REG_WORTIME1   = 0x36; // High byte of WOR timer
static const uint8_t REG_WORTIME0   = 0x37; // Low byte of WOR timer
static const uint8_t REG_PKTSTATUS  = 0x38; // Current GDOx status and packet status
static const uint8_t REG_VCO_VC_DAC = 0x39; // Current setting from PLL calibration module
static const uint8_t REG_TXBYTES    = 0x3A; // Underflow and number of bytes in the TX FIFO
static const uint8_t REG_RXBYTES    = 0x3B; // Overflow and number of bytes in the RX FIFO
static const uint8_t REG_RCCTRL1_STATUS = 0x3C; // Last RC oscillator calibration result
static const uint8_t REG_RCCTRL2_STATUS = 0x3D; // Last RC oscillator calibration result

static const uint8_t REG_PATABLE    = 0x3E; // Output Power Programming
static const uint8_t REG_FIFO    = 0x3F;

static const uint8_t VAL_IOCFG2_DEFAULT   = 0x29; // CHIP_RDYn
static const uint8_t VAL_IOCFG1_DEFAULT   = 0x2E; // High impedance (3-state)
static const uint8_t VAL_IOCFG0_DEFAULT   = 0x3F;
static const uint8_t VAL_IOCFG0_TEMPERATURE = 0x80;
static const uint8_t VAL_FIFOTHR_DEFAULT  = 0x07;
static const uint8_t VAL_PKTLEN_DEFAULT   = 0xFF;
static const uint8_t VAL_PKTCTRL1_DEFAULT = 0x04;
static const uint8_t VAL_PKTCTRL0_DEFAULT = 0x45;
static const uint8_t VAL_ADDR_DEFAULT     = 0x00;
static const uint8_t VAL_ADDR     = 0x01;
static const uint8_t VAL_FSCTRL1_DEFAULT  = 0x0F;
static const uint8_t VAL_FSCTRL1  = 0x09;
static const uint8_t VAL_FSCTRL0_DEFAULT  = 0x00;
static const uint8_t VAL_FREQ2    = 0x5D;
static const uint8_t VAL_FREQ1_DEFAULT    = 0xC4;
static const uint8_t VAL_FREQ1    = 0x93;
static const uint8_t VAL_FREQ0_DEFAULT    = 0xEC;
static const uint8_t VAL_FREQ0    = 0xB1;
static const uint8_t VAL_MDMCFG4_DEFAULT = 0x8C;
static const uint8_t VAL_MDMCFG4  = 0x2D;
static const uint8_t VAL_MDMCFG3_DEFAULT = 0x22;
static const uint8_t VAL_MDMCFG3  = 0x3B;
static const uint8_t VAL_MDMCFG2_DEFAULT = 0x02;
static const uint8_t VAL_MDMCFG2  = 0x73; // Modulation format MSK
static const uint8_t VAL_MDMCFG1_DEFAULT = 0x22;
static const uint8_t VAL_MDMCFG1  = 0xA2;
static const uint8_t VAL_MDMCFG0_DEFAULT = 0xF8;
static const uint8_t VAL_DEVIATN_DEFAULT = 0x47;
//static const uint8_t VAL_DEVIATN  = 0x01;
//static const uint8_t VAL_MCSM2    = 0x07;
//static const uint8_t VAL_MCSM1    = 0x30;
static const uint8_t VAL_MCSM0_DEFAULT = 0x36;
static const uint8_t VAL_MCSM0    = 0x18; // Automatically calibrate when going from IDLE to RX or TX (or FSTXON)
static const uint8_t VAL_FOCCFG_DEFAULT = 0x36;
static const uint8_t VAL_FOCCFG   = 0x1D;
static const uint8_t VAL_BSCFG_DEFAULT = 0x6C;
static const uint8_t VAL_BSCFG    = 0x1C;
static const uint8_t VAL_AGCCTRL2 = 0xC7;

// AGCCTRL2 – AGC Control settings
// Reduces the maximum allowable DVGA gain.
static const uint8_t MAX_DVGA_GAIN_ALL = 0b00000000; // All gain settings can be used
static const uint8_t MAX_DVGA_GAIN_1   = 0b01000000; // The highest gain setting can not be used
static const uint8_t MAX_DVGA_GAIN_2   = 0b10000000; // The 2 highest gain settings can not be used
static const uint8_t MAX_DVGA_GAIN_3   = 0b11000000; // The 3 highest gain settings can not be used
// Sets the maximum allowable LNA + LNA 2 gain relative to the
// maximum possible gain.
static const uint8_t MAX_LNA_GAIN_MAX_GAIN       = 0b00000000; // Maximum possible LNA + LNA 2 gain
static const uint8_t MAX_LNA_GAIN_2_6DB_BELOW_MAX_GAIN  = 0b00001000; // Approx. 2.6 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_6_1DB_BELOW_MAX_GAIN  = 0b00010000; // Approx. 6.1 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_7_4DB_BELOW_MAX_GAIN  = 0b00011000; // Approx. 7.4 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_9_2DB_BELOW_MAX_GAIN  = 0b00100000; // Approx. 9.2 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_11_5DB_BELOW_MAX_GAIN = 0b00101000; // Approx. 11.5 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_14_6DB_BELOW_MAX_GAIN = 0b00110000; // Approx. 14.6 dB below maximum possible gain
static const uint8_t MAX_LNA_GAIN_17_1DB_BELOW_MAX_GAIN = 0b00111000; // Approx. 17.1 dB below maximum possible gain
// These bits set the target value for the averaged amplitude from
// the digital channel filter (1 LSB = 0 dB).
static const uint8_t MAGN_TARGET_24DB = 0b00000000;
static const uint8_t MAGN_TARGET_27DB = 0b00000001;
static const uint8_t MAGN_TARGET_30DB = 0b00000010;
static const uint8_t MAGN_TARGET_33DB = 0b00000011;
static const uint8_t MAGN_TARGET_36DB = 0b00000100;
static const uint8_t MAGN_TARGET_38DB = 0b00000101;
static const uint8_t MAGN_TARGET_40DB = 0b00000110;
static const uint8_t MAGN_TARGET_42DB = 0b00000111;
// Resets AGCCTRL2 to default settings
static const uint8_t VAL_AGCCTRL2_DEFAULT = 0x03;

static const uint8_t VAL_AGCCTRL1       = 0x00;
static const uint8_t VAL_AGCCTRL1_DEFAULT = 0x40;
static const uint8_t VAL_AGCCTRL0       = 0xB2;
static const uint8_t VAL_AGCCTRL0_DEFAULT = 0x91;
//static const uint8_t VAL_WOREVT1  = 0x87;
//static const uint8_t VAL_WOREVT0  = 0x6B;
//static const uint8_t VAL_WORCTRL  = 0xF8;
static const uint8_t VAL_FREND1_DEFAULT   = 0x56;
static const uint8_t VAL_FREND0_DEFAULT   = 0x10;
static const uint8_t VAL_FSCAL3_DEFAULT   = 0xA9;
static const uint8_t VAL_FSCAL2_DEFAULT   = 0x0A;
static const uint8_t VAL_FSCAL1_DEFAULT   = 0x20;
static const uint8_t VAL_FSCAL0_DEFAULT   = 0x0D;
static const uint8_t VAL_RCCTRL1_DEFAULT  = 0x41;
static const uint8_t VAL_RCCTRL0_DEFAULT  = 0x00;
static const uint8_t VAL_FSTEST_DEFAULT   = 0x59;
static const uint8_t VAL_PTEST_DEFAULT    = 0x7F;
static const uint8_t VAL_TEST2_DEFAULT    = 0x88;
static const uint8_t VAL_TEST1_DEFAULT    = 0x31;
static const uint8_t VAL_TEST0_DEFAULT    = 0x0B;

enum class Modulation : uint8_t {
	TWO_FSK = 0b000,
	GFSK = 0b001,
	OOK = 0b011,
	MSK = 0b111
};

struct Command {
	uint8_t device_address = 0;
	uint8_t channel;
//	Modulation modulation = Modulation::TWO_FSK;
//	bool manchester_encoding = false;
	uint8_t length;
	uint8_t *data;
};

class CC2500Client;

class CC2500Component: public Component, public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST,
		spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_2MHZ> {
public:
	void setup() override;
	void loop() override;
	void dump_config() override;

	void set_gdo0_pin(InternalGPIOPin *gdo0_pin) {
		this->gdo0_pin_ = gdo0_pin;
	}
	InternalGPIOPin* get_gdo0_pin() {
		return this->gdo0_pin_;
	}
	void set_gdo2_pin(InternalGPIOPin *gdo2_pin) {
		this->gdo2_pin_ = gdo2_pin;
	}
	void set_output_power(uint8_t output_power) {
		this->output_power_ = output_power;
	}

	void add_device(CC2500Client *device);
	void send(Command command);
protected:
	void receive_();
	void reset_();
	uint8_t write_reg_(uint8_t address, uint8_t value);
	void write_reg_(uint8_t address, uint8_t *data, uint8_t length);
	void send_strobe_(uint8_t strobe);
	static void IRAM_ATTR receive_interrupt_(CC2500Component *cc2500);

	InternalGPIOPin *gdo0_pin_{nullptr};
	InternalGPIOPin *gdo2_pin_{nullptr};
	// 0xBB -2dB
	// 0xFE 0dB
	// 0xFF +1dB
	optional<uint8_t> output_power_;
	std::vector<CC2500Client *> devices_;
	uint8_t max_packet_length_ = 0;

	uint8_t commands_sent_ = 0;

	bool busy_ = false;
};

/**
 * Base class for CC2500Device, un-templated.
 */
class CC2500Client {
public:
	CC2500Client(uint8_t device_address, uint8_t channel, uint8_t packet_length) :
		packet_length(packet_length), device_address_(device_address), channel_(channel) {
	}

	void set_parent(CC2500Component *parent);
	void send(uint8_t *data, uint8_t length);
	virtual bool receive(uint8_t *data, uint8_t length, float rssi, uint8_t lqi) {
		return this->receive(data, length);
	}
	virtual bool receive(uint8_t *data, uint8_t length) {
		return false;
	}
	uint8_t packet_length;
protected:
	CC2500Component *parent_ { nullptr };
	uint8_t device_address_;
	uint8_t channel_;
};

/**
 * The CC2500Device is what components using the CC2500 will create.
 *
 * @tparam DEVICE_ADDRESS
 * @tparam CHANNEL
 */
template<uint8_t DEVICE_ADDRESS, uint8_t CHANNEL, uint8_t PACKET_LENGTH>
class CC2500Device: public CC2500Client {
public:
	CC2500Device() :
			CC2500Client(DEVICE_ADDRESS, CHANNEL, PACKET_LENGTH) {
	}
};


}  // namespace cc2500
}  // namespace esphome
