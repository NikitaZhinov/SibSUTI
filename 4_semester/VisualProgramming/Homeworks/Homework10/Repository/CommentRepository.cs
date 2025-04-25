using Homework10.Model;

namespace Homework10.Repository
{
    public class CommentRepository : ICommentRepository
    {
        private readonly Dictionary<int, Comment> _comments = [];
        private int _nextId = 1;

        public Comment AddComment(int postId, string name, string email, string body)
        {
            var comment = new Comment()
            {
                Id = _nextId++,
                PostId = postId,
                Name = name,
                Email = email,
                Body = body
            };

            _comments.Add(comment.Id, comment);
            return comment;
        }

        public Comment? GetComment(int id)
        {
            _comments.TryGetValue(id, out var comment);
            return comment;
        }

        public IEnumerable<Comment> GetComments()
        {
            return _comments.Values;
        }

        public bool RemoveComment(int id)
        {
            return _comments.Remove(id);
        }

        public Comment? UpdateComment(int id, int postId, string name, string email, string body)
        {
            if (!_comments.ContainsKey(id))
                return null;

            var updatedComment = new Comment()
            {
                Id = id,
                PostId = postId,
                Name = name,
                Email = email,
                Body = body
            };

            _comments[id] = updatedComment;
            return updatedComment;
        }
    }
}