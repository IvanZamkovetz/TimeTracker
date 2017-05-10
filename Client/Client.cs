using System;
using System.Threading;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class Server
    {
        public NamedPipeClientStream pipeClient;
        string pipeName;
        int pipeBufSize;
        public byte[] writeBuffer;
        public byte[] readBuffer;

        public Server()
        {
            this.pipeClient = new NamedPipeClientStream(".", "mainpipe", PipeDirection.InOut, PipeOptions.None, TokenImpersonationLevel.Impersonation);
        }
        public Server(string pipeName = "mainpipe")
        {
            this.pipeName = pipeName; 
            this.pipeClient = new NamedPipeClientStream(".", pipeName, PipeDirection.InOut, PipeOptions.None, TokenImpersonationLevel.Impersonation);
        }
        public bool Connect()
        {
            Console.WriteLine("Connecting to server...\n");
            this.pipeClient.Connect();

            if (!this.pipeClient.IsConnected)
            {
                Console.WriteLine("Client connecting error. \n");
                return false;
            }

            this.pipeBufSize = this.pipeClient.OutBufferSize;
            this.writeBuffer = new byte[this.pipeClient.OutBufferSize];
            this.readBuffer = new byte[this.pipeClient.InBufferSize];

            return true;
        }
        public void Disconnect()
        {
            this.pipeClient.Close();
        }
        public void MainProc()
        {
            while (this.Write())
            {
                Thread.Sleep(1000);
                this.Read();
                Thread.Sleep(1000);

            }
        }
        public bool Write()
        {
            string command = "GetHash;userId;taskId;12:00;";//Console.ReadLine();
            if (command == "stop")
            {
                return false;
            }
            byte[] request = Encoding.ASCII.GetBytes(command);
            for (int i = 0; i < this.pipeBufSize; i++)
            {
                this.writeBuffer[i] = 0;
            }
            request.CopyTo(this.writeBuffer, 0);

            this.pipeClient.Write(this.writeBuffer, 0, writeBuffer.Count());
            return true;
        }
        public void Read()
        {
            for (int i = 0; i < this.pipeBufSize; i++)
            {
                this.readBuffer[i] = 0;
            }
            this.pipeClient.Read(this.readBuffer, 0, this.readBuffer.Count());
            Console.WriteLine(Encoding.ASCII.GetString(this.readBuffer));
        }
    }


    class Client
    {
        static void Main(string[] args)
        {
            //System.Diagnostics.Process win32Server = System.Diagnostics.Process.Start("D:\\polygon\\netVs13\\NamedPipes\\Debug\\Win32Server.exe");

            Server server = new Server();
            if (!server.Connect())
            {
                return;
            }
            Thread tMainProc = new Thread(server.MainProc);
            tMainProc.Start();
            tMainProc.Join();

            server.Disconnect();
        }
    }
}
