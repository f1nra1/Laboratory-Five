class Program
{
    const int MAX_PER_CELL = 10;
    const int NUM_ZONES = 3;
    const int NUM_SHELVES = 14;
    const int NUM_SECTIONS = 6;
    const int NUM_LEVELS = 20;
    const int TOTAL_CELLS = NUM_ZONES * NUM_SHELVES * NUM_SECTIONS * NUM_LEVELS;
    const int TOTAL_CAPACITY = TOTAL_CELLS * MAX_PER_CELL;

    static Dictionary<string, Dictionary<string, int>> warehouse = new();
    static HashSet<string> allAddresses = new();
    static char[] zones = { 'A', 'B', 'V' };

    static void PrintHelp()
    {
        Console.WriteLine("\nДоступные команды:");
        Console.WriteLine("  ADD <товар> <кол-во> <адрес>     - добавить товар");
        Console.WriteLine("  REMOVE <товар> <кол-во> <адрес>  - удалить товар");
        Console.WriteLine("  INFO                             - информация о складе");
        Console.WriteLine("  EXIT                             - выход из программы");
    }

    static void InitAddresses()
    {
        foreach (char zone in zones)
        {
            for (int shelf = 1; shelf <= NUM_SHELVES; shelf++)
            {
                for (int section = 1; section <= NUM_SECTIONS; section++)
                {
                    for (int level = 1; level <= NUM_LEVELS; level++)
                    {
                        string addr = $"{zone}{shelf:D2}{section}{level}";
                        allAddresses.Add(addr);
                    }
                }
            }
        }
    }

    static bool IsValidAddress(string address)
    {
        return allAddresses.Contains(address);
    }

    static void AddItem(string name, int count, string address)
    {
        if (count <= 0)
        {
            Console.WriteLine("Ошибка: количество должно быть положительным.");
            return;
        }

        if (!IsValidAddress(address))
        {
            Console.WriteLine($"Ошибка: неверный адрес {address}");
            return;
        }

        int total = warehouse.ContainsKey(address)
            ? warehouse[address].Values.Sum()
            : 0;

        if (total + count > MAX_PER_CELL)
        {
            Console.WriteLine($"Ошибка: ячейка {address} переполнена.");
            return;
        }

        if (!warehouse.ContainsKey(address))
        {
            warehouse[address] = new Dictionary<string, int>();
        }

        if (!warehouse[address].ContainsKey(name))
        {
            warehouse[address][name] = 0;
        }

        warehouse[address][name] += count;
        Console.WriteLine($"Добавлено: {name} x{count} в {address}");
    }

    static void RemoveItem(string name, int count, string address)
    {
        if (count <= 0)
        {
            Console.WriteLine("Ошибка: количество должно быть положительным.");
            return;
        }

        if (!IsValidAddress(address))
        {
            Console.WriteLine($"Ошибка: неверный адрес {address}");
            return;
        }

        if (!warehouse.ContainsKey(address) || !warehouse[address].ContainsKey(name) || warehouse[address][name] < count)
        {
            Console.WriteLine($"Ошибка: недостаточно товара в {address}");
            return;
        }

        warehouse[address][name] -= count;
        if (warehouse[address][name] == 0)
        {
            warehouse[address].Remove(name);
        }
        if (warehouse[address].Count == 0)
        {
            warehouse.Remove(address);
        }

        Console.WriteLine($"Удалено: {name} x{count} из {address}");
    }

    static void Info()
    {
        int used = 0;
        Dictionary<char, int> zoneUsed = new();

        foreach (var kvp in warehouse)
        {
            string addr = kvp.Key;
            int cellTotal = kvp.Value.Values.Sum();
            used += cellTotal;
            char zone = addr[0];

            if (!zoneUsed.ContainsKey(zone))
                zoneUsed[zone] = 0;

            zoneUsed[zone] += cellTotal;
        }

        Console.WriteLine("\n--- Состояние склада ---");
        double totalPercent = 100.0 * used / TOTAL_CAPACITY;
        Console.WriteLine($"Общая загруженность склада: {totalPercent:F2}%");

        foreach (char zone in zones)
        {
            double zoneCapacity = NUM_SHELVES * NUM_SECTIONS * NUM_LEVELS * MAX_PER_CELL;
            double zonePercent = zoneUsed.ContainsKey(zone) ? 100.0 * zoneUsed[zone] / zoneCapacity : 0;
            Console.WriteLine($"Зона {zone}: {zonePercent:F2}%");
        }

        Console.WriteLine("\nЗанятые ячейки:");
        foreach (var (addr, items) in warehouse)
        {
            Console.Write($"{addr}: ");
            foreach (var (name, count) in items)
            {
                Console.Write($"{name} {count}; ");
            }
            Console.WriteLine();
        }

        Console.WriteLine("\nПустые ячейки:");
        foreach (var addr in allAddresses)
        {
            if (!warehouse.ContainsKey(addr))
                Console.Write($"{addr} ");
        }
        Console.WriteLine();
    }

    static void Main()
    {
        InitAddresses();
        PrintHelp();

        while (true)
        {
            Console.Write("\n> ");
            string? line = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(line)) continue;

            string[] parts = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length == 0) continue;

            string command = parts[0].ToUpperInvariant();

            if (command == "ADD" && parts.Length == 4)
            {
                string name = parts[1];
                if (int.TryParse(parts[2], out int count))
                    AddItem(name, count, parts[3]);
                else
                    Console.WriteLine("Ошибка: неверный формат количества.");
            }
            else if (command == "REMOVE" && parts.Length == 4)
            {
                string name = parts[1];
                if (int.TryParse(parts[2], out int count))
                    RemoveItem(name, count, parts[3]);
                else
                    Console.WriteLine("Ошибка: неверный формат количества.");
            }
            else if (command == "INFO")
            {
                Info();
            }
            else if (command == "EXIT")
            {
                Console.WriteLine("Завершение работы программы.");
                break;
            }
            else
            {
                Console.WriteLine("Неизвестная команда.");
                PrintHelp();
            }
        }
    }
}