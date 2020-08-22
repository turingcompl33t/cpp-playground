### C++ Casting

Add some clever comment here.

### C++ Casts Summary

|                           | Generate Code | Generate Data | Risky? | Data Type          |
|---------------------------|---------------|---------------|--------|--------------------|
| Object Casting            |               |               |        |                    |
| `static_cast`               | YES           | YES           | 2      | Any Types          |
|                           |               |               |        |                    |
| Pointer/Reference Casting |               |               |        |                    |
| `static_cast`               | NO            | NO            | 4      | Related            |
| `dynamic_cast`              | YES           | NO            | 3      | Related (Downcast) |
| `const_cast`                | NO            | NO            | 1      | Same Types         |
| `reinterpret_cast`          | NO            | NO            | 5      | Any Types          |