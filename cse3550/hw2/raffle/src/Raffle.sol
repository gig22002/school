// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

contract Raffle {
	address payable owner;
	address[] tickets;
	mapping(address => uint8) registered;
	event _registered(address addr, uint256 refunded);
	event deregistered(address addr);
	uint256 potAmt;
	uint256 regFee = type(uint256).max;
	uint256 ticketPrice;
	event boughtTicket(address addr, uint8 n);
	uint32 curPlayers = 0;
	uint32 minPlayers;
	event winner(address addr, uint256 _amt);

	constructor() public {
		owner = payable(msg.sender);
		//move setup to constructor
	}
	
	function setUpRaffle(uint256 _regFee, uint256 _price, uint32 _min) public payable {
		require(msg.sender==owner, "Must be owner to set up");

		potAmt = msg.value;
		regFee = _regFee;
		ticketPrice = _price;
		minPlayers = _min;
	}

	function register() public payable {
		require(msg.value>=regFee, "Insufficient value");
		require(msg.sender!=owner, "Owner cannot register");
		require(curPlayers<minPlayers+1, "Reached max participants");
		require(registered[msg.sender]==0, "Participant already registered");

		//Initialize registree
		registered[msg.sender] = 1;
		curPlayers++;
		potAmt+=regFee;

		if (msg.value>regFee) {
			payable(msg.sender).transfer(msg.value-regFee);
		}
		emit _registered(msg.sender, msg.value-regFee);

	}

	function deregister() public {
		require(registered[msg.sender]==1, "Participant not registered");
		require(!checkTicketed(msg.sender), "Particpant already bought ticket");
		require(curPlayers<minPlayers, "Reached max participants");

		registered[msg.sender] = 0;
		curPlayers--;
		payable(msg.sender).transfer(regFee);
		potAmt-=regFee;
		emit deregistered(msg.sender);
	}

	function purchaseTicket(uint8 _amt) public payable {
		require(registered[msg.sender]!=0, "Participant not registered");
		require(curPlayers<minPlayers, "Reached max participants");
		require(msg.value>=_amt*ticketPrice, "Insufficient value");
		require(countTickets(msg.sender)+_amt<20, "Cannot exceed 20 tickets");

		potAmt += _amt*ticketPrice;
		for (uint8 i=0; i<_amt; i++)
			tickets.push(msg.sender);

		if (msg.value > _amt*ticketPrice)
			payable(msg.sender).transfer(msg.value-_amt*ticketPrice);
		emit boughtTicket(msg.sender, _amt);

	}

	function checkTicketed(address addr) public view returns (bool) {
		for (uint256 i=0; i<tickets.length; i++){
			if(tickets[i]==addr)
				return true;
		}
		return false;
	}
	
	function countTickets(address addr) public view returns (uint8) {
		uint8 sum = 0;
		for (uint256 i=0; i<tickets.length; i++){
			if(tickets[i]==addr)
				sum++;
		}
		return sum;
	}
	
	function pickWinner() public {
		require(msg.sender==owner, "Must be owner to pick");
		require(curPlayers>=minPlayers, "Minimum players not reached");
		uint256 picked = uint256(sha256(abi.encodePacked(block.timestamp, blockhash(block.number-1)))) % (tickets.length+1);
		//use built in block random
		if(picked == 0) {
			owner.transfer(potAmt);
			emit winner(owner, potAmt);
			potAmt=0;
			return;
		}
		
		payable(tickets[picked]).transfer(potAmt);
		emit winner(tickets[picked], potAmt);
		potAmt=0;
	}
}
