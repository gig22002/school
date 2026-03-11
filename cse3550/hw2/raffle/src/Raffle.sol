// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

contract Raffle {
	address payable owner;
	event failedInit(address addr);
	mapping(address => uint256) registered;
	event failedReg(address addr);
	uint256 potAmt;
	uint256 regFee;
	uint256 ticketPrice;
	uint256 minPlayers;

	constructor() public {
		owner = payable(msg.sender);
	}
	
	function setUpRaffle(uint256 _pot, uint256 _regFee, uint256 _price, uint256 _min) public {
		if(msg.sender != owner) {
			emit failedInit(msg.sender);
			return;
		}

		potAmt = _pot;
		regFee = _regFee;
		ticketPrice = _price;
		minPlayers = _min;
	}

	function register() public payable {
		if (msg.value<regFee || msg.sender == owner) {
			emit failedReg(msg.sender);
			return;
		}
		//Initialize registree
		registered[msg.sender] = 0;
		owner.transfer(regFee);

		if (msg.value>regFee) {
			payable(msg.sender).transfer(msg.value-regFee);
		}

	}
	
}
