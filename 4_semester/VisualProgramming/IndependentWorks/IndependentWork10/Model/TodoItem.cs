namespace IndependentWork10.Model
{
    public class TodoItem
    {
        private readonly DateTime createdAt = DateTime.Now;

        public int Id { get; set; }
        public required string Title { get; set; }
        public string? Description { get; set; }
        public bool IsCompleted { get; set; }
        public DateTime CreatedAt { get { return createdAt; } }
    }
}
