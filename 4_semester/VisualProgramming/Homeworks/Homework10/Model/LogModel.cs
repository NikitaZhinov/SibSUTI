namespace Homework10.Model
{
    public class LogModel
    {
        private readonly DateTime time = DateTime.Now;

        public int Id { get; set; }
        public required string Type { get; set; }
        public required string Info { get; set; }
        public DateTime Time { get { return time; } }

    }
}
