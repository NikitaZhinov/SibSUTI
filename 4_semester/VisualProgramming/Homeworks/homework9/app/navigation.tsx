import { NavLink } from "react-router";

export default function Navigation() {
  return (
    <nav className="Navigation">
      <ul>
        <li>
          <NavLink to="/">Comments</NavLink>
        </li>
        <li>
          <NavLink to="/albums">Albums</NavLink>
        </li>
        <li>
          <NavLink to="/posts">Posts</NavLink>
        </li>
        <li>
          <NavLink to="/todos">ToDoSS</NavLink>
        </li>
        <li>
          <NavLink to="/users">Users</NavLink>
        </li>
      </ul>
    </nav>
  );
}
