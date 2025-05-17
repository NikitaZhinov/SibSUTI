using Homework10.Model;
using Microsoft.EntityFrameworkCore;

namespace Homework10.Repository
{
    public class ApplicationContext : DbContext
    {
        public DbSet<Comment> Comments { get; set; }
        public DbSet<LogModel> Logs { get; set; }

        // Create database on first request
        public ApplicationContext()
        { Database.EnsureCreated(); }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql("Host=localhost;" +
                                     "Port=5432;" +
                                     "Database=homework10;" +
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
                return new_comment;
            }
            return null;
        }

        public Comment? GetComment(int id)
        { return Comments.Find(id); }

        public LogModel AddLog(LogModel log)
        {
            Add(log);
            SaveChanges();
            return log;
        }

        public LogModel? GetLog(int id)
        { return Logs.Find(id); }
    }
}
