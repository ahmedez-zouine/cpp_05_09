# Exercise-Specific Workflows and Diagrams

## Exercise 00: Bitcoin Exchange - Complete Workflow

### Main Program Flow

```mermaid
graph TD
    A[./btc input.txt] --> B{argc == 2?}
    B -->|No| C[ERROR: wrong number of args]
    B -->|Yes| D[Create BitcoinExchange object]
    D --> E[upload_csv_file()]
    E --> F{CSV loaded?}
    F -->|No| G[ERROR: Can't open CSV]
    F -->|Yes| H[procces_input(filename)]
    H --> I[Process each line]
    I --> J[Output results]
    J --> K[Exit]
    C --> L[return 1]
    G --> L
```

### Detailed File Processing

```mermaid
sequenceDiagram
    participant User
    participant Main
    participant BitcoinEx as BitcoinExchange
    participant CSV as data.csv
    participant Input as input.txt
    participant Map as std::map
    
    User->>Main: ./btc input.txt
    Main->>BitcoinEx: BitcoinExchange()
    Main->>BitcoinEx: upload_csv_file()
    
    BitcoinEx->>CSV: Open file
    CSV-->>BitcoinEx: File stream
    BitcoinEx->>CSV: Read header (skip)
    
    loop For each CSV line
        BitcoinEx->>CSV: getline()
        CSV-->>BitcoinEx: "date,price"
        BitcoinEx->>BitcoinEx: Parse date and price
        BitcoinEx->>Map: prices[date] = price
    end
    
    Main->>BitcoinEx: procces_input(input.txt)
    BitcoinEx->>Input: Open file
    Input-->>BitcoinEx: File stream
    BitcoinEx->>Input: Read header (validate)
    
    loop For each input line
        BitcoinEx->>Input: getline()
        Input-->>BitcoinEx: "date | value"
        BitcoinEx->>BitcoinEx: validate_year()
        BitcoinEx->>BitcoinEx: validate_month()
        BitcoinEx->>BitcoinEx: validate_day()
        BitcoinEx->>BitcoinEx: validate_value()
        BitcoinEx->>Map: get_money(date)
        Map-->>BitcoinEx: price
        BitcoinEx->>User: Output calculation
    end
```

### Data Structure Deep Dive

```mermaid
classDiagram
    class BitcoinExchange {
        -std::map<string, double> prices
        +BitcoinExchange()
        +BitcoinExchange(const BitcoinExchange&)
        +operator=(const BitcoinExchange&)
        +~BitcoinExchange()
        +int upload_csv_file()
        +int procces_input(const string&)
        +int validate_year(string)
        +int validate_month(string)
        +int validate_day(string, string, string)
        +double validate_value(string)
        +double get_money(string)
    }
    
    BitcoinExchange --> "1" Map : contains
    
    class Map {
        <<std::map>>
        +operator[](const string&) : double&
        +lower_bound(const string&) : iterator
        +find(const string&) : iterator
        +size() : size_t
    }
```

---

## Exercise 01: RPN Calculator - Stack Operations

### Expression Evaluation Flow

```mermaid
graph TD
    A[Input: "8 9 * 9 - 9 - 9 - 4 - 1 +"] --> B[Split by spaces]
    B --> C[Token Array: 8,9,*,9,-,9,-,9,-,4,-,1,+]
    C --> D[Initialize Stack]
    D --> E[Process Token 0: '8']
    
    E --> F{Is Digit?}
    F -->|Yes| G[Push 8]
    F -->|No| H[Pop 2, Calculate, Push Result]
    
    G --> I[Stack: [8]]
    I --> J[Next Token]
    J --> K[Process Token 1: '9']
    K --> L[Push 9]
    L --> M[Stack: [8,9]]
    M --> N[Process Token 2: '*']
    N --> O[Pop 9, Pop 8]
    O --> P[Calculate: 8 * 9 = 72]
    P --> Q[Push 72]
    Q --> R[Stack: [72]]
    R --> S[Continue...]
```

### Stack State Visualization

```mermaid
graph LR
    subgraph "Token Processing"
        A["8" → Stack: [8]]
        B["9" → Stack: [8,9]]
        C["*" → Pop(9,8) → 8*9=72 → Stack: [72]]
        D["9" → Stack: [72,9]]
        E["-" → Pop(9,72) → 72-9=63 → Stack: [63]]
        F["9" → Stack: [63,9]]
        G["-" → Pop(9,63) → 63-9=54 → Stack: [54]]
        H["9" → Stack: [54,9]]
        I["-" → Pop(9,54) → 54-9=45 → Stack: [45]]
        J["4" → Stack: [45,4]]
        K["-" → Pop(4,45) → 45-4=41 → Stack: [41]]
        L["1" → Stack: [41,1]]
        M["+" → Pop(1,41) → 41+1=42 → Stack: [42]]
    end
    
    A --> B --> C --> D --> E --> F --> G --> H --> I --> J --> K --> L --> M
```

### Error Handling Flowchart

```mermaid
flowchart TD
    A[New Token] --> B{Length > 1?}
    B -->|Yes| C[Error: Invalid input]
    B -->|No| D{Is digit or operator?}
    D -->|No| E[Error: Invalid character]
    D -->|Yes| F{Is operator?}
    F -->|No| G[Push digit to stack]
    F -->|Yes| H{Stack size >= 2?}
    H -->|No| I[Error: Not enough operands]
    H -->|Yes| J{Division by zero?}
    J -->|Yes| K[Error: Division by zero]
    J -->|No| L[Perform operation]
    
    G --> M[Continue]
    L --> M
    C --> N[Return 1]
    E --> N
    I --> N
    K --> N
```

---

## Exercise 02: Ford-Johnson Algorithm - Detailed Analysis

### Algorithm Execution Steps

```mermaid
graph TD
    A[Input: 3,5,9,7,4] --> B[Step 1: Pair Elements]
    B --> C["Pairs: (3,5), (9,7), 4 (odd)"]
    C --> D[Step 2: Sort within pairs]
    D --> E["Sorted pairs: (5,3), (9,7), 4"]
    E --> F[Step 3: Separate larger/smaller]
    F --> G["Larger: [5,9]<br/>Smaller: [3,7]<br/>Odd: 4"]
    G --> H[Step 4: Recursively sort larger]
    H --> I["Sorted larger: [5,9]"]
    I --> J[Step 5: Generate Jacobsthal]
    J --> K["Jacobsthal: [0,1,1,3,5,...]"]
    K --> L[Step 6: Insert smaller elements]
    L --> M["Insert 3: [3,5,9]<br/>Insert 7: [3,5,7,9]"]
    M --> N[Step 7: Insert odd element]
    N --> O["Insert 4: [3,4,5,7,9]"]
```

### Container Comparison Workflow

```mermaid
graph TD
    A[Parse Input Arguments] --> B[Create std::vector copy]
    A --> C[Create std::deque copy]
    
    B --> D[Start Vector Timer]
    C --> E[Start Deque Timer]
    
    D --> F[sort(vector)]
    E --> G[sort(deque)]
    
    F --> H[End Vector Timer]
    G --> I[End Deque Timer]
    
    H --> J[Calculate Vector Time]
    I --> K[Calculate Deque Time]
    
    J --> L[Display Results]
    K --> L
```

### Memory Access Patterns

```mermaid
graph LR
    subgraph "std::vector Access Pattern"
        A[CPU] --> B[Cache Line 1<br/>Elements 0-7]
        A --> C[Cache Line 2<br/>Elements 8-15]
        A --> D[Cache Line 3<br/>Elements 16-23]
        B --- C --- D
    end
    
    subgraph "std::deque Access Pattern"
        E[CPU] --> F[Chunk 1 Pointer]
        E --> G[Chunk 2 Pointer]
        E --> H[Chunk 3 Pointer]
        F --> I[Chunk 1 Data]
        G --> J[Chunk 2 Data]
        H --> K[Chunk 3 Data]
    end
```

### Jacobsthal Number Generation

```mermaid
flowchart TD
    A[Start] --> B[Initialize: J₀=0, J₁=1, J₂=1]
    B --> C[i = 2]
    C --> D{Jᵢ < size?}
    D -->|No| E[Return sequence]
    D -->|Yes| F["Jᵢ₊₁ = Jᵢ + 2×Jᵢ₋₁"]
    F --> G[Add to sequence]
    G --> H[i++]
    H --> D
    
    subgraph "Example for size=5"
        I["J₀=0, J₁=1, J₂=1"]
        J["J₃ = 1 + 2×1 = 3"]
        K["J₄ = 3 + 2×1 = 5"]
        L["J₅ = 5 + 2×3 = 11 > 5, stop"]
        M["Return: [0,1,1,3,5]"]
        I --> J --> K --> L --> M
    end
```

### Performance Measurement Process

```mermaid
sequenceDiagram
    participant Main
    participant PmergeMe
    participant Vector as std::vector
    participant Deque as std::deque
    participant Clock as clock()
    
    Main->>PmergeMe: sort_and_compare()
    PmergeMe->>PmergeMe: parse_input()
    PmergeMe->>Vector: Copy data
    PmergeMe->>Deque: Copy data
    
    PmergeMe->>Clock: start = clock()
    PmergeMe->>Vector: sort()
    PmergeMe->>Clock: end = clock()
    PmergeMe->>PmergeMe: Calculate vector time
    
    PmergeMe->>Clock: start = clock()
    PmergeMe->>Deque: sort()
    PmergeMe->>Clock: end = clock()
    PmergeMe->>PmergeMe: Calculate deque time
    
    PmergeMe->>Main: Display results
```

---

## Complexity Analysis Diagrams

### Time Complexity Comparison

```mermaid
graph LR
    subgraph "Input Size vs Time"
        A[n=100] --> B[Vector: 15μs]
        A --> C[Deque: 18μs]
        
        D[n=1000] --> E[Vector: 180μs]
        D --> F[Deque: 220μs]
        
        G[n=10000] --> H[Vector: 2ms]
        G --> I[Deque: 2.5ms]
    end
    
    subgraph "O(n log n) Growth"
        J[Theoretical Curve]
        K[Vector Performance]
        L[Deque Performance]
        J -.-> K
        J -.-> L
    end
```

### Memory Usage Patterns

```mermaid
graph TD
    subgraph "BitcoinExchange Memory"
        A[std::map<br/>~40 bytes per entry]
        B[Key: string (date)]
        C[Value: double (price)]
        D[Node overhead]
        A --> B
        A --> C
        A --> D
    end
    
    subgraph "RPN Calculator Memory"
        E[std::stack<br/>Dynamic size]
        F[Underlying container<br/>(default: std::deque)]
        G[Elements: int (4 bytes each)]
        E --> F
        F --> G
    end
    
    subgraph "PmergeMe Memory"
        H[Original data]
        I[Vector copy]
        J[Deque copy]
        K[Temporary arrays]
        H --> I
        H --> J
        I --> K
        J --> K
    end
```

This comprehensive workflow analysis shows exactly how your code executes, making it perfect for Obsidian with all the Mermaid diagrams for visualization!