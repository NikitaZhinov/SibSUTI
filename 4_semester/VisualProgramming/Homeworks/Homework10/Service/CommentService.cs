using Homework10.Model;
using Homework10.Repository;

namespace Homework10.Service
{
    public class CommentService(ICommentRepository commentRepository)
    {
        private readonly ICommentRepository _commentRepository = commentRepository;

        public Comment AddComment(Comment comment)
        {
            return _commentRepository.AddComment(
                comment.PostId,
                comment.Name,
                comment.Email,
                comment.Body);
        }

        public bool RemoveComment(int id)
        {
            return _commentRepository.RemoveComment(id);
        }

        public Comment? UpdateComment(int id, Comment comment)
        {
            return _commentRepository.UpdateComment(
                id,
                comment.PostId,
                comment.Name,
                comment.Email,
                comment.Body);
        }

        public Comment? GetComment(int id)
        {
            return _commentRepository.GetComment(id);
        }

        public IEnumerable<Comment> GetComments()
        {
            return _commentRepository.GetComments();
        }
    }
}