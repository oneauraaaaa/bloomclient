using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace BloomPrivateInjector
{
    internal class Program
    {
        static void clearAndWriteBloomText()
        {

            string art = @" ░▒▓███████▓▒░░▒▓█▓▒░ ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓██████████████▓▒░
 ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░
 ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░
 ░▒▓███████▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░
 ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░
 ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░
 ░▒▓███████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░

                                                          Private by oneaura
";
            Console.Clear();
            Console.WriteLine();
            Console.WriteLine(art);
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int processId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out IntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, out IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool CloseHandle(IntPtr hObject);

        // Constants for process access and memory allocation
        const uint PROCESS_ALL_ACCESS = 0x1F0FFF;
        const uint MEM_COMMIT = 0x1000;
        const uint MEM_RESERVE = 0x2000;
        const uint PAGE_READWRITE = 0x04;
        static void Main(string[] args)
        {

            string confirmationInput;

            // Ensure Unicode blocks render correctly
            Console.OutputEncoding = Encoding.UTF8;
            Console.Title = "Bloom Private Injector";

            clearAndWriteBloomText();
            Console.WriteLine("                          ");
            Console.WriteLine(" => Are you sure you want to inject Bloom Private? (yes/no): ");
            confirmationInput = Console.ReadLine();

            if(confirmationInput == null || !confirmationInput.Equals("yes", StringComparison.OrdinalIgnoreCase))
            {
                clearAndWriteBloomText();
                Console.WriteLine("Injection cancelled by user.");
                return;
            }
            clearAndWriteBloomText();

            //Console.Write("Bloom Injecting ");
            //using (var progress = new ProgressBar())
            //{
            //    for (int i = 0; i <= 100; i++)
            //    {
            //        progress.Report((double)i / 100);
            //        Thread.Sleep(1);
            //    }
            //}
            clearAndWriteBloomText();
            // Get the path to the DLL in the same directory as the executable
            string dllName = "bloomclient.dll";
            string dllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, dllName);

            if (!File.Exists(dllPath))
            {
                Console.WriteLine($"Error: {dllName} not found in {AppDomain.CurrentDomain.BaseDirectory}");
                Console.ReadLine();
                return;
            }

            // Convert DLL path to absolute path
            dllPath = Path.GetFullPath(dllPath);

            // Find javaw.exe process
            Process[] processes = Process.GetProcessesByName("javaw");
            if (processes.Length == 0)
            {
                Console.WriteLine("Error: javaw.exe process not found.");
                Console.ReadLine();
                return;
            }

            // Use the first javaw.exe process found
            Process targetProcess = processes[0];
            int processId = targetProcess.Id;
            Console.WriteLine($"Found javaw.exe with PID: {processId}");

            // Open the target process
            IntPtr hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
            if (hProcess == IntPtr.Zero)
            {
                Console.WriteLine($"Error: Failed to open process. Error Code: {Marshal.GetLastWin32Error()}");
                Console.ReadLine();
                return;
            }

            // Allocate memory in the target process for the DLL path
            byte[] dllPathBytes = Encoding.ASCII.GetBytes(dllPath + "\0");
            IntPtr allocMemAddress = VirtualAllocEx(hProcess, IntPtr.Zero, (uint)dllPathBytes.Length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (allocMemAddress == IntPtr.Zero)
            {
                Console.WriteLine($"Error: Failed to allocate memory in target process. Error Code: {Marshal.GetLastWin32Error()}");
                Console.ReadLine();
                CloseHandle(hProcess);
                return;
            }

            // Write the DLL path to the allocated memory
            if (!WriteProcessMemory(hProcess, allocMemAddress, dllPathBytes, (uint)dllPathBytes.Length, out IntPtr bytesWritten))
            {
                Console.WriteLine($"Error: Failed to write DLL path to target process. Error Code: {Marshal.GetLastWin32Error()}");
                Console.ReadLine();
                CloseHandle(hProcess);
                return;
            }

            // Get the address of LoadLibraryA
            IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            if (loadLibraryAddr == IntPtr.Zero)
            {
                Console.WriteLine($"Error: Failed to get LoadLibraryA address. Error Code: {Marshal.GetLastWin32Error()}");
                Console.ReadLine();
                CloseHandle(hProcess);
                return;
            }

            // Create a remote thread in the target process to load the DLL
            IntPtr hThread = CreateRemoteThread(hProcess, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, out IntPtr threadId);
            if (hThread == IntPtr.Zero)
            {
                Console.WriteLine($"Error: Failed to create remote thread. Error Code: {Marshal.GetLastWin32Error()}");
                Console.ReadLine();
                CloseHandle(hProcess);
                return;
            }
            clearAndWriteBloomText();
            Console.WriteLine("Bloom Injected!");
            Console.ReadLine();
            CloseHandle(hThread);
            CloseHandle(hProcess);
        }
    }
}
