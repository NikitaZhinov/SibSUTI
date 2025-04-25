import { type RouteConfig, index, route } from "@react-router/dev/routes";

export default [
    index("routes/home/home.tsx"),

    route("albums", "routes/albums/albums.tsx"),
    route("posts", "routes/posts/posts.tsx"),
    route("todos", "routes/todos/todos.tsx"),
    route("users", "routes/users/users.tsx"),
] satisfies RouteConfig;
