// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

contract Raffle {
	address payable owner;
	event failedInit(address addr);
	mapping(address => int32) registered;
	event failedReg(address addr);
	event deregistered(address addr);
	uint256 potAmt;
	uint256 regFee = type(uint256).max;
	uint256 ticketPrice;
	uint256 minPlayers;

	constructor() public {
		owner = payable(msg.sender);
	}
	
	function setUpRaffle(uint256 _regFee, uint256 _price, uint256 _min) public payable {
		if(msg.sender != owner) {
			emit failedInit(msg.sender);
			return;
		}

		potAmt = msg.value;
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
		registered[msg.sender] = 1;

		if (msg.value>regFee) {
			payable(msg.sender).transfer(msg.value-regFee);
		}

	}

	function deregister() public {
		if (registered[msg.sender] == 0)
			return;
		registered[msg.sender] = 0;
		payable(msg.sender).transfer(regFee);
		emit deregistered(msg.sender);
	}
	
}
