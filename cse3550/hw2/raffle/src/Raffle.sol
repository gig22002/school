// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13

contract Raffle {
	address payable owner;
	mapping(address => uint256) registered;
	event failedReg(address addr);
	uint256 potAmt;
	uint256 regFee;
	uint256 ticketPrice;
	uint256 minPlayers;

	constructor() public {
		owner = payable(msg.sender);
	}

	function register(address registree, uint256 amt) public {
		if (amt<regFee) {
			emit failedReg(registree)
			return 0;
		}
	}
	
}
