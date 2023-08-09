# วิธีใช้งาน
- เปิดสวิตช์อุปกรณ์
- ใส่หลอดด้าย หันด้านบาร์โค๊ดให้ตรงกับลูกศร
- ใส่กำบังในจุดอ่าน หันด้านตัดมุมให้ตรง

# เงื่อนไขการทำงาน
|   Detect                               |  Machinery   |   Lamp Alarm   |  Lamp Ready  |
|   ----------------------------------   |  --------    |   ----------   |  ----------  |
|   no thread, no card                   |  OFF         |   OFF          |  OFF         |
|   with thread, no card                 |  OFF         |   OFF          |  BLINK       |
|   no thread, have card                 |  OFF         |   OFF          |  BLINK       |
|   The thread and the card do not match |	OFF         |	ON           |  OFF         |
|   The thread and the card match        |  ON          |   OFF          |  ON          |

