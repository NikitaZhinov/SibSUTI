using IndependentWork10.Model;
using IndependentWork10.Repository;

namespace IndependentWork10.Service
{
    public class TodoItemService(ITodoItemRepository repository)
    {
        private readonly ITodoItemRepository _repository = repository;

        public TodoItem Add(TodoItem item)
        { return _repository.Add(item); }

        public IEnumerable<TodoItem> GetAll()
        { return _repository.GetAll(); }

        public TodoItem? GetById(int id)
        { return _repository.GetById(id); }

        public bool RemoveById(int id)
        { return _repository.RemoveById(id); }

        public bool UpdateById(int id, TodoItem new_item)
        { return _repository.UpdateById(id, new_item); }
    }
}
