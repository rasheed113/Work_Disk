/* Dashboard presentation/controller. Search is delegated to the authoritative Search Tool boundary. */
import { SearchTool } from '../../tools/lifecycle/search/search_tool';

export function dashboardSearchPlaceholder(): string {
  return '🔎 Search Dashboard...';
}

export function createDashboardSearch(tool: SearchTool) {
  return (command: unknown) => tool.handle(command as never);
}
