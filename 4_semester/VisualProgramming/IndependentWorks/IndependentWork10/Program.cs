using IndependentWork10.Model;
using IndependentWork10.Repository;
using IndependentWork10.Service;

var builder = WebApplication.CreateBuilder(args);

// Adding a policy to allow accepting requests from all addresses
builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAll", policy =>
    {
        policy.AllowAnyOrigin().AllowAnyMethod().AllowAnyHeader();
    });
});

// --------------------------- Add Singletons ---------------------------
builder.Services.AddSingleton<ITodoItemRepository, TodoItemRepository>();
builder.Services.AddSingleton<TodoItemService>();

var app = builder.Build();

app.UseCors("AllowAll"); // It is allowed to accept requests from all addresses

// --------------------------- Routes ---------------------------
app.MapGet("/api/todo", (TodoItemService todoItemService) => Results.Ok(todoItemService.GetAll()));

app.MapGet("/api/todo/{id}", (int id, TodoItemService todoItemService) =>
{
    var item = todoItemService.GetById(id);
    return item == null ? Results.NotFound() : Results.Ok(item);
});

app.MapPost("/api/todo", (TodoItem item, TodoItemService todoItemService) => Results.Ok(todoItemService.Add(item)));

app.MapPut("/api/todo/{id}", (int id, TodoItem item, TodoItemService todoItemService) => todoItemService.UpdateById(id, item) ?
                                                                                                             Results.Ok(item) :
                                                                                                             Results.NotFound());

app.MapDelete("api/todo/{id}", (int id, TodoItemService todoItemService) => todoItemService.RemoveById(id) ?
                                                                                            Results.Ok(id) :
                                                                                            Results.NotFound());

app.Run();
