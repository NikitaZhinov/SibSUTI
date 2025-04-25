using Homework10.Model;
using Homework10.Repository;
using Homework10.Service;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAll", policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyMethod()
              .AllowAnyHeader();
    });
});

builder.Services.AddSingleton<ICommentRepository, CommentRepository>();
builder.Services.AddSingleton<CommentService>();

var app = builder.Build();

app.UseCors("AllowAll");

// Get all comments
app.MapGet("/comments", (CommentService commentService) =>
    Results.Ok(commentService.GetComments()));

// Get comment by ID
app.MapGet("/comments/{id}", (int id, CommentService commentService) =>
{
    var comment = commentService.GetComment(id);
    return comment is not null ? Results.Ok(comment) : Results.NotFound();
});

// Add new comment
app.MapPost("/comments", (Comment comment, CommentService commentService) =>
{
    var createdComment = commentService.AddComment(comment);
    return Results.Created($"/comments/{createdComment.Id}", createdComment);
});

// Update comment
app.MapPatch("/comments/{id}", (int id, Comment comment, CommentService commentService) =>
{
    var updatedComment = commentService.UpdateComment(id, comment);
    return updatedComment is not null ? Results.Ok(updatedComment) : Results.NotFound();
});

// Delete comment
app.MapDelete("/comments/{id}", (int id, CommentService commentService) =>
{
    var isDeleted = commentService.RemoveComment(id);
    return isDeleted ? Results.NoContent() : Results.NotFound();
});

app.Run();