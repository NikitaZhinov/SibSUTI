using Homework10.Model;
using Microsoft.EntityFrameworkCore;

namespace Homework11.Repository
{
    public class ApplicationContext : DbContext
    {
        public DbSet<Comment> Comments { get; set; }

        // Create database on first request
        public ApplicationContext(DbContextOptions<ApplicationContext> options) : base(options)
        { Database.EnsureCreated(); }

        // Create database on first request
        public ApplicationContext()
        { Database.EnsureCreated(); }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql("Host=localhost;" +
                                     "Port=5432;" +
                                     "Database=usersdb;" +
                                     "Username=postgres;" +
                                     "Password=2208");
        }

        public Comment AddComment(Comment comment)
        {
            Add(comment);
            SaveChanges();
            return comment;
        }

        public bool RemoveComment(int id)
        {
            var comment = Comments.Find(id);
            if (comment != null)
                Remove(comment);
            SaveChanges();
            return comment != null;
        }

        public Comment? UpdateComment(int id, Comment new_comment)
        {
            var comment = Comments.Find(id);
            if (comment != null)
            {
                new_comment.Id = id;
                RemoveComment(id);
                AddComment(new_comment);
            }
            return comment;
        }

        public Comment? GetComment(int id)
        { return Comments.Find(id); }
    }
}
