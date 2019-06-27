basic.forever(function(){
    if(pins.digitalReadPin(DigitalPin.P13) == 1){
        bitboard.sendstr("x")
    }
    if(pins.digitalReadPin(DigitalPin.P14) == 1){
        bitboard.sendstr("y")
    }
    if(pins.digitalReadPin(DigitalPin.P15) == 1){
        bitboard.sendstr("z")
    }
    if(pins.digitalReadPin(DigitalPin.P8) == 1){
        bitboard.sendstr("w")
    }
    basic.pause(100)
})