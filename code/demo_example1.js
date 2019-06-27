basic.forever(function(){
    if(pins.analogReadPin(AnalogPin.P0) < 221) {
        if(pins.digitalReadPin(DigitalPin.P13) == 1){
            bitboard.sendfunckey(BBFuncKeys.Space)
        }
        if(pins.digitalReadPin(DigitalPin.P14) == 1){
            bitboard.sendfunckey(BBFuncKeys.Backspace)
        }
        if(pins.digitalReadPin(DigitalPin.P15) == 1){
            bitboard.sendfunckey(BBFuncKeys.Tab)
        }
        if(pins.digitalReadPin(DigitalPin.P16) == 1){
            bitboard.sendfunckey(BBFuncKeys.Enter)
        }
    }
    else if(pins.analogReadPin(AnalogPin.P0) < 330){
        if(pins.digitalReadPin(DigitalPin.P13) == 1){
            bitboard.sendstr("+")
        }
        if(pins.digitalReadPin(DigitalPin.P14) == 1){
            bitboard.sendstr("-")
        }
        if(pins.digitalReadPin(DigitalPin.P15) == 1){
            bitboard.sendstr("*")
        }
        if(pins.digitalReadPin(DigitalPin.P16) == 1){
            bitboard.sendstr("/")
        }
    }
    else if(pins.analogReadPin(AnalogPin.P0) < 559){
        if(pins.digitalReadPin(DigitalPin.P13) == 1){
            bitboard.sendstr("1")
        }
        if(pins.digitalReadPin(DigitalPin.P14) == 1){
            bitboard.sendstr("2")
        }
        if(pins.digitalReadPin(DigitalPin.P15) == 1){
            bitboard.sendstr("3")
        }
        if(pins.digitalReadPin(DigitalPin.P16) == 1){
            bitboard.sendstr("4")
        }
    }
    else {
        if(pins.digitalReadPin(DigitalPin.P13) == 1){
            bitboard.sendstr("A")
        }
        if(pins.digitalReadPin(DigitalPin.P14) == 1){
            bitboard.sendstr("B")
        }
        if(pins.digitalReadPin(DigitalPin.P15) == 1){
            bitboard.sendstr("C")
        }
        if(pins.digitalReadPin(DigitalPin.P16) == 1){
            bitboard.sendstr("D")
        }
    }
    basic.pause(100)
    if(pins.analogReadPin(AnalogPin.P1) < 51){
        bitboard.godirections(BBDirections.Left)
    }
    if(pins.analogReadPin(AnalogPin.P1) > 973){
        bitboard.godirections(BBDirections.Right)
    }
    if(pins.analogReadPin(AnalogPin.P2) < 51){
        bitboard.godirections(BBDirections.Down)
    }
    if(pins.analogReadPin(AnalogPin.P2) > 973){
        bitboard.godirections(BBDirections.Up)
    }
    basic.pause(50)
})
