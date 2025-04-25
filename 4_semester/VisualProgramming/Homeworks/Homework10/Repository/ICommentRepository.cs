using Homework10.Model;

namespace Homework10.Repository
{
    public interface ICommentRepository
    {
        Comment AddComment(int postId, string name, string email, string body);
        bool RemoveComment(int id);
        Comment? UpdateComment(int id, int postId, string name, string email, string body);
        Comment? GetComment(int id);
        IEnumerable<Comment> GetComments();
    }
}