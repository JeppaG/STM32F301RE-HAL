.. code:: robotframework

  *** Settings ***
  Library    SerialLibrary    encoding=ascii
  Library    String
  Suite Setup    Open Serial Port
  Suite Teardown  Close Serial Port

  *** Variables ***
  ${SERIAL_PORT}       /dev/ttyACM0

  *** Test cases ****
  MCU echos input string
    [Timeout]            5s
    Write Data           Hussa\r
    ${read} =            Read until single    Hussa\r
    Should Contain       ${read}              Hussa\r

  *** Keywords ***
  Open Serial Port
    Add Port    ${SERIAL_PORT}
    ...         baudrate=115200
    ...         bytesize=8
    ...         parity=N
    ...         stopbits=1
    ...         timeout=999

  Close Serial Port
    Delete All Ports

  Read Until Single
    [Arguments]    ${expected}
    ${read} =        Read Until    terminator=${expected}
    Should Contain   ${read}    ${expected}
    Log              ${read}    console=yes
    RETURN           ${read}


