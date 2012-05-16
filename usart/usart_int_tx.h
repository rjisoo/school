FUNCTION Main
  Enable TX Interrupt
  Enable Global Interrupts

  LOOP FOREVER
    {Do Stuff}
    Transmit_Data(Data)
    Sleep
  END LOOP
END FUNCTION

FUNCTION Transmit_Data(Data)
  IF (UDR NOT FULL)
    Store Data into RingBuffer
  ELSE
    UDR = Data
  END IF
END FUNCTION

ISR TX_ISR
  IF RingBuffer NOT EMPTY
    UDR = RingBuffer.Next
  END IF
END ISR 
