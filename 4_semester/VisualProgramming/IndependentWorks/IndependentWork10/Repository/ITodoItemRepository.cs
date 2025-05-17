using IndependentWork10.Model;

namespace IndependentWork10.Repository
{
    public interface ITodoItemRepository
    {
        TodoItem Add(TodoItem item);

        bool UpdateById(int id, TodoItem new_item);

        bool RemoveById(int id);

        IEnumerable<TodoItem> GetAll();

        TodoItem? GetById(int id);
    }
}
