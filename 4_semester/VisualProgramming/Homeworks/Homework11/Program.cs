using Homework10.Model;
using Homework10.Repository;
using Homework10.Service;
using Homework11.Repository;
using Microsoft.EntityFrameworkCore;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory.Database;

var builder = WebApplication.CreateBuilder(args);

// Adding a policy to allow accepting requests from all addresses
builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAll", policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyMethod()
              .AllowAnyHeader();
    });
});

// --------------------------- Data Base Context ---------------------------
builder.Services.AddDbContext<ApplicationContext>(options => options.UseNpgsql());

// --------------------------- Add Singletons ---------------------------
builder.Services.AddSingleton<ICommentRepository, CommentRepository>();
builder.Services.AddSingleton<CommentService>();

var app = builder.Build();

app.UseCors("AllowAll"); // It is allowed to accept requests from all addresses

// --------------------------- Routes ---------------------------
// Get all comments
app.MapGet("/comments", (ApplicationContext applicationContext) => Results.Ok(applicationContext.Comments));

// Get comment by ID
app.MapGet("/comments/{id}", (int id, ApplicationContext applicationContext) =>
{
    var comment = applicationContext.GetComment(id);
    return comment is not null ? Results.Ok(comment) : Results.NotFound();
});

// Add new comment
app.MapPost("/comments", (Comment comment, ApplicationContext applicationContext) =>
{
    var createdComment = applicationContext.AddComment(comment);
    return Results.Created($"/comments/{createdComment.Id}", createdComment);
});

// Update comment
app.MapPatch("/comments/{id}", (int id, Comment comment, ApplicationContext applicationContext) =>
{
    var updatedComment = applicationContext.UpdateComment(id, comment);
    return updatedComment is not null ? Results.Ok(updatedComment) : Results.NotFound();
});

// Delete comment
app.MapDelete("/comments/{id}", (int id, ApplicationContext applicationContext) =>
{
    var isDeleted = applicationContext.RemoveComment(id);
    return isDeleted ? Results.NoContent() : Results.NotFound();
});

app.Run();
