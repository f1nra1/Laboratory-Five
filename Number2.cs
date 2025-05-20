using System.Text;

class Program
{
    class Patient
    {
        public string Ticket { get; set; }
        public int Duration { get; set; }
    }

    class Window
    {
        public int TotalTime { get; set; } = 0;
        public List<Patient> Assigned { get; } = new List<Patient>();
    }

    static Random rng = new Random();

    static string GenerateTicket()
    {
        int number = rng.Next(0, 1000);
        return "T" + number.ToString("D3");
    }

    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.WriteLine(">>> Введите кол-во окон");
        Console.Write("<<< ");
        if (!int.TryParse(Console.ReadLine(), out int windowCount) || windowCount <= 0)
        {
            Console.WriteLine(">>> Ошибка: введите положительное число.");
            return;
        }
        Queue<Patient> queue = new();
        string? input;
        while (true)
        {
            Console.Write("<<< ");
            input = Console.ReadLine();
            if (input == null) continue;
            if (input.StartsWith("ENQUEUE"))
            {
                if (int.TryParse(input.Substring(8), out int duration) && duration > 0)
                {
                    string ticket = GenerateTicket();
                    queue.Enqueue(new Patient { Ticket = ticket, Duration = duration });
                    Console.WriteLine($">>> {ticket}");
                }
                else
                {
                    Console.WriteLine(">>> Ошибка: продолжительность должна быть положительным числом.");
                }
            }
            else if (input == "DISTRIBUTE")
            {
                List<Window> windows = new();
                for (int i = 0; i < windowCount; i++)
                    windows.Add(new Window());

                while (queue.Count > 0)
                {
                    Patient p = queue.Dequeue();

                    int minIndex = 0;
                    for (int i = 1; i < windowCount; i++)
                    {
                        if (windows[i].TotalTime < windows[minIndex].TotalTime)
                            minIndex = i;
                    }

                    windows[minIndex].Assigned.Add(p);
                    windows[minIndex].TotalTime += p.Duration;
                }

                for (int i = 0; i < windowCount; i++)
                {
                    Console.Write($">>> Окно {i + 1} ({windows[i].TotalTime} минут): ");
                    for (int j = 0; j < windows[i].Assigned.Count; j++)
                    {
                        Console.Write(windows[i].Assigned[j].Ticket);
                        if (j + 1 < windows[i].Assigned.Count)
                            Console.Write(", ");
                    }
                    Console.WriteLine();
                }

                break; // Завершение после DISTRIBUTE
            }
            else
            {
                Console.WriteLine(">>> Неизвестная команда.");
            }
        }
    }
}
