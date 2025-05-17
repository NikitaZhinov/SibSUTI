using Homework10.Model;
using Homework10.Repository;
using Homework10.Service;

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
builder.Services.AddDbContext<ApplicationContext>();

// --------------------------- Add Singletons ---------------------------
builder.Services.AddSingleton<ICommentRepository, CommentRepository>();
builder.Services.AddSingleton<CommentService>();

var app = builder.Build();

app.UseCors("AllowAll"); // It is allowed to accept requests from all addresses

// --------------------------- Routes ---------------------------
// Get all comments
app.MapGet("/comments", (ApplicationContext applicationContext) =>
{
    return Results.Ok(applicationContext.Comments);
});

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
    applicationContext.AddLog(new LogModel
    {
        Type = "Info",
        Info = $"Add a new comment with data: Id = {createdComment.Id}, " +
                                            $"Name = {createdComment.Name}, " +
                                            $"PostId = {createdComment.PostId}, " +
                                            $"Email = {createdComment.Email}, " +
                                            $"Body = {createdComment.Body}."
    });
    return Results.Created($"/comments/{createdComment.Id}", createdComment);
});

// Update comment
app.MapPatch("/comments/{id}", (int id, Comment comment, ApplicationContext applicationContext) =>
{
    var updatedComment = applicationContext.UpdateComment(id, comment);
    if (updatedComment is not null)
        applicationContext.AddLog(new LogModel
        {
            Type = "Info",
            Info = $"Update the comment with Id = {id}. New data: Name = {updatedComment.Name}, " +
                                                                $"PostId = {updatedComment.PostId}, " +
                                                                $"Email = {updatedComment.Email}, " +
                                                                $"Body = {updatedComment.Body}."
        });
    else
        applicationContext.AddLog(new LogModel
        {
            Type = "Error",
            Info = $"Failed update the comment: The comment with Id = {id} is not exist!"
        });
    return updatedComment is not null ? Results.Ok(updatedComment) : Results.NotFound();
});

// Delete comment
app.MapDelete("/comments/{id}", (int id, ApplicationContext applicationContext) =>
{
    var isDeleted = applicationContext.RemoveComment(id);
    if (isDeleted)
        applicationContext.AddLog(new LogModel
        {
            Type = "Info",
            Info = $"Remove the comment with Id = {id}."
        });
    else
        applicationContext.AddLog(new LogModel
        {
            Type = "Error",
            Info = $"Failed removing the comment: The comment with Id = {id} is not exist!"
        });
    return isDeleted ? Results.NoContent() : Results.NotFound();
});

app.MapGet("/logs", (ApplicationContext applicationContext) => Results.Ok(applicationContext.Logs));

app.Run();
