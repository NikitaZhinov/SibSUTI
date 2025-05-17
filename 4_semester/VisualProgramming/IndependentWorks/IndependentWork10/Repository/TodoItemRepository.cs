using IndependentWork10.Model;

namespace IndependentWork10.Repository
{
    public class TodoItemRepository : ITodoItemRepository
    {
        private readonly Dictionary<int, TodoItem> data = [];
        private int nextId = 0;

        public TodoItem Add(TodoItem item)
        {
            item.Id = nextId;
            data.Add(nextId++, item);
            return item;
        }

        public IEnumerable<TodoItem> GetAll()
        { return data.Values; }

        public TodoItem? GetById(int id)
        {
            data.TryGetValue(id, out var item);
            return item;
        }

        public bool RemoveById(int id)
        {
            data.TryGetValue(id, out var item);
            if (item != null) data.Remove(id);
            return item != null;
        }

        public bool UpdateById(int id, TodoItem new_item)
        {
            data.TryGetValue(id, out var item);
            if (item != null)
            {
                new_item.Id = id;
                data[id] = new_item;
            }
            return item != null;
        }
    }
}
